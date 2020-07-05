#include "presistence.h"
#include "index/memory_rbtree.h"
#include "cache/main_cache.h"



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
		}

		bool PresistenceHandler::writeRow(int id, std::vector<Value> values)
		{
			Row row(tablePtr_, id, values);
			int offset = indexPtr_->addIndexUnit(row.id);
			obito::file::writeToFile(tablePtr_->getDataFileName(), row.toBinary(), valueRowSize_, offset);
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

			int offset = indexPtr_->getOffset(id);
			char* buffer = (char*)malloc(valueRowSize_);
			obito::file::readFromFile(tablePtr_->getDataFileName(), buffer, valueRowSize_, offset);
			Row row(tablePtr_, buffer);
			free(buffer);
			cachePtr_->addToCache(row);
			return row;
		}

		bool PresistenceHandler::deleteRow(int id)
		{
			indexPtr_->deleteIndexUnit(id);
			cachePtr_->deleteFromCache(id);
			return true;
		}

} }