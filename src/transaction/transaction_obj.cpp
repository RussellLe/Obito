#include "transaction_obj.h"



namespace obito {
	namespace transaction {

		TransactionObject::TransactionObject(int theTransactionId,const TablePresistenceMap& tablePresistenceMap)
		{
			transactionId = theTransactionId;
			tablePresistenceMap_ = tablePresistenceMap;
		}

		TransactionObject::~TransactionObject()
		{
			//
		}

		bool TransactionObject::addRow(std::string tableName, Row row)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);

			row.setTransactionId(transactionId);
			return presistencePtr->addRow(row);
		}

		Row TransactionObject::readRow(std::string tableName, int id)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			return presistencePtr->readRow(id);
		}

		bool TransactionObject::deleteRow(std::string tableName, int id)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			return presistencePtr->deleteRow(id);
		}

		bool TransactionObject::updateRow(std::string tableName, Row row)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			row.setTransactionId(transactionId);

			if (!presistencePtr->deleteRow(row.id))
			{
				return false;
			}

			if (!presistencePtr->addRow(row))
			{
				return false;
			}

			return true;
		}

	}
}