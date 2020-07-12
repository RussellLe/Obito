#include "presistence.h"
#include "index/memory_rbtree.h"
#include "cache/main_cache.h"
#include "bufferpool/main_buffer_pool.h"
#include "mvcc/versionchain/main_version_chain.h"



namespace obito {
	namespace presistence {

		PresistenceHandler::PresistenceHandler(std::shared_ptr<Table> tablePtr, std::vector<Column> columns)
		{
			tablePtr_ = tablePtr;
			tablePtr_->columns = columns;
			valueRowSize_ = tablePtr_->getValueRowSize();


			indexPtr_ = std::make_shared<obito::index::MemoryRBTree>(obito::common::generateIndexFileName(tablePtr_->tableName),
				obito::common::generateIndexFragsFileName(tablePtr_->tableName), valueRowSize_);
			cachePtr_ = std::make_shared<obito::cache::MainCache>();
			bufferPtr_ = std::make_shared<obito::buffer::MainBufferPool>();
			versionChainPtr_ = std::make_shared<obito::versionchain::MainVersionChain>();
		}

		PresistenceHandler::~PresistenceHandler()
		{
			flushBuffer_();
		}

		bool PresistenceHandler::addRow(Row row)
		{
			if (bufferPtr_->checkIdExist(row.id))
			{
				return false;
			}

			if (cachePtr_->checkIdExist(row.id))
			{
				return false;
			}

			if (indexPtr_->checkIdExist(row.id))
			{
				return false;
			}

			if (!addRow_(row))
			{
				return false;
			}
			return true;
		}

		bool PresistenceHandler::writeRow(Row row)
		{
			int offset = indexPtr_->addIndexUnit(row.id);
			obito::file::writeToFile(tablePtr_->getDataFileName(), row.toBinary(), valueRowSize_, offset);
			return true;
		}

		bool PresistenceHandler::writeRows(std::vector<Row> rows)
		{
			if (rows.empty())
			{
				return false;
			}
			char* writeBufferTmp = (char*)malloc(valueRowSize_ * rows.size());
			int memcpyOffset = 0;

			std::vector<int> idVec;
			for (auto iter = rows.begin(); iter < rows.end(); iter++)
			{
				idVec.push_back(iter->id);
				memcpy(writeBufferTmp + memcpyOffset, iter->toBinary(), valueRowSize_);
				memcpyOffset += valueRowSize_;
			}
			int startOffset = indexPtr_->addIndexUnits(idVec);

			obito::file::writeToFile(tablePtr_->getDataFileName(), writeBufferTmp, valueRowSize_ * rows.size(), startOffset);
		}

		Row PresistenceHandler::readRow(int id)
		{
			if (cachePtr_->checkIdExist(id))		//read from cache first
			{
				return cachePtr_->readFromCache(id);
			}

			if (bufferPtr_->checkIdExist(id))
			{
				Row row = bufferPtr_->readFromBuffer(id);
				cachePtr_->addToCache(row);
				return row;
			}

			int offset = indexPtr_->getOffset(id);
			if (offset == -1)
			{
				Row errorRow;
				errorRow.id = ERROR_ROW_FLAG;
				errorRow.setTransactionId(ERROR_ROW_FLAG);
				return errorRow;
			}

			char* buffer = (char*)malloc(valueRowSize_);
			obito::file::readFromFile(tablePtr_->getDataFileName(), buffer, valueRowSize_, offset);
			Row row(tablePtr_, buffer);
			free(buffer);
			cachePtr_->addToCache(row);
			return row;
		}

		Row PresistenceHandler::readVersionChain(int id, int transactionId)
		{
			return versionChainPtr_->readRow(id, transactionId);
		}

		bool PresistenceHandler::deleteRow(int id, int transactionId)
		{
			versionChainPtr_->addRow(readRow(id));
			if (!deleteRow_(id))
			{
				return false;
			}
			Row versionRow;
			versionRow.id = id;
			versionRow.setTransactionId(transactionId);
			versionChainPtr_->addRow(versionRow);
		}

		bool PresistenceHandler::deleteRow_(int id)
		{
			if (bufferPtr_->checkIdExist(id))
			{
				bufferPtr_->deleteFromBuffer(id);
			}

			indexPtr_->deleteIndexUnit(id);
			cachePtr_->deleteFromCache(id);
			return true;
		}

		bool PresistenceHandler::updateRow(Row row)
		{
			versionChainPtr_->addRow(readRow(row.id));

			if (!deleteRow_(row.id))
			{
				return false;
			}
			if (!addRow_(row))
			{
				return false;
			}
			return true;
		}

		bool PresistenceHandler::flushBuffer_()
		{
			std::vector<Row> rows = bufferPtr_->getRowsFromBuffer();
			bufferPtr_->cleanBuffer();
			writeRows(rows);
			return true;
		}

		bool PresistenceHandler::addRow_(Row row)
		{
			bufferPtr_->addToBuffer(row);

			if (bufferPtr_->getFlushStatus())
			{
				flushBuffer_();
			}
			return true;
		}

		bool PresistenceHandler::rollback(int transactionId, std::vector<int> updateIdVec)
		{
			for (auto iter = updateIdVec.begin(); iter < updateIdVec.end(); iter++)
			{
				Row row = readRow(*iter);
				if (row.transactionId == transactionId)
				{
					Row preRow = versionChainPtr_->readLatestRow(row.id);
					updateRow(preRow);
					continue;
				}
				if (row.id == ERROR_ROW_FLAG)
				{
					Row latestRow = versionChainPtr_->readLatestRow(*iter);
					if (latestRow.transactionId == transactionId)
					{
						versionChainPtr_->deleteRow(*iter, transactionId);
						addRow(latestRow);
						continue;
					}
				}

				versionChainPtr_->deleteRow(*iter, transactionId);
			}

			return true;
		}

} }