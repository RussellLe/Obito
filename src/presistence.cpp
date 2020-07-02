#include "presistence.h"
#include "index/memory_rbtree.h"



namespace obito {
	namespace presistence {

		PresistenceHandler::PresistenceHandler(std::shared_ptr<Table> tablePtr, std::vector<Column> columns)
		{
			tablePtr_ = tablePtr;
			tablePtr_->columns = columns;
			valueRowSize_ = tablePtr_->getValueRowSize();
			indexPtr_ = std::make_shared<obito::index::MemoryRBTree>(obito::common::generateIndexFileName(tablePtr_->tableName),
				obito::common::generateIndexFragsFileName(tablePtr_->tableName), valueRowSize_);
		}

		bool PresistenceHandler::writeRow(int id, std::vector<Value> values)
		{
			Row row(tablePtr_, id, values);
			int offset = indexPtr_->addIndexUnit(row.id);
			obito::file::writeToFile(tablePtr_->getDataFileName(), row.toBinary(), valueRowSize_, offset);
			return true;
		}

		bool PresistenceHandler::writeRow(int id, Row row)
		{
			int offset = indexPtr_->addIndexUnit(row.id);
			obito::file::writeToFile(tablePtr_->getDataFileName(), row.toBinary(), valueRowSize_, offset);
			return true;
		}

		Row PresistenceHandler::readRow(int id)
		{
			int offset = indexPtr_->getOffset(id);

			char* buffer = (char*)malloc(valueRowSize_);
			obito::file::readFromFile(tablePtr_->getDataFileName(), buffer, valueRowSize_, offset);
			Row row(tablePtr_, buffer);
			free(buffer);

			return row;
		}

		bool PresistenceHandler::deleteRow(int id)
		{
			indexPtr_->deleteIndexUnit(id);
			return true;
		}

} }