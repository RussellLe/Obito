#include "transaction_obj.h"



namespace obito {
	namespace transaction {

		TransactionObject::TransactionObject(int theTransactionId, int theLeftEndTransactionId, TransactionIsolationLevel isolationLevel,
			const TablePresistenceMap& tablePresistenceMap)
		{
			transactionId = theTransactionId;
			tablePresistenceMap_ = tablePresistenceMap;
			leftEndTransactionId = theLeftEndTransactionId;
			isolationLevel_ = isolationLevel;
		}

		TransactionObject::~TransactionObject()
		{
			//
		}

		bool TransactionObject::addRow(std::string tableName, Row row)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			row.setTransactionId(transactionId);

			auto updateIdVecIter = updateIdMap_.find(tableName);
			if (updateIdVecIter == updateIdMap_.end())
			{
				updateIdMap_[tableName] = *(new std::vector<int>());
				updateIdVecIter = updateIdMap_.find(tableName);
			}
			updateIdVecIter->second.push_back(row.id);
			return presistencePtr->addRow(row);
		}

		Row TransactionObject::readRow(std::string tableName, int id, int rightEndTransactionId)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			Row newestRow = presistencePtr->readRow(id);

			switch (isolationLevel_)
			{
			case LOW_ISOLATION_LEVEL:
				return newestRow;

			case MEDIUM_ISOLATION_LEVEL:
				if (newestRow.transactionId == transactionId)
				{
					return newestRow;
				}
				if (newestRow.transactionId > rightEndTransactionId)
				{
					return presistencePtr->readVersionChain(id, rightEndTransactionId);
				}
				break;

			case HIGH_ISOLATION_LEVEL:
				if (newestRow.transactionId == transactionId)
				{
					return newestRow;
				}
				Row nowTransactionRow = presistencePtr->readVersionChain(id, transactionId);
				if (nowTransactionRow.id != ERROR_ROW_FLAG)
				{
					return nowTransactionRow;
				}
				return presistencePtr->readVersionChain(id, leftEndTransactionId);

			}
			return newestRow;
		}

		bool TransactionObject::deleteRow(std::string tableName, int id)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);

			auto updateIdVecIter = updateIdMap_.find(tableName);
			if (updateIdVecIter == updateIdMap_.end())
			{
				updateIdMap_[tableName] = *(new std::vector<int>());
				updateIdVecIter = updateIdMap_.find(tableName);
			}
			updateIdVecIter->second.push_back(id);
			return presistencePtr->deleteRow(id, transactionId);
		}

		bool TransactionObject::updateRow(std::string tableName, Row row)
		{
			auto presistencePtr = tablePresistenceMap_.getPresistence(tableName);
			row.setTransactionId(transactionId);
			
			auto updateIdVecIter = updateIdMap_.find(tableName);
			if (updateIdVecIter == updateIdMap_.end())
			{
				updateIdMap_[tableName] = *(new std::vector<int>());
				updateIdVecIter = updateIdMap_.find(tableName);
			}
			updateIdVecIter->second.push_back(row.id);
			return presistencePtr->updateRow(row);
		}

		bool TransactionObject::rollback()
		{
			bool flag = true;
			for (auto iter = updateIdMap_.begin(); iter != updateIdMap_.end(); iter++)
			{
				auto presistencePtr = tablePresistenceMap_.getPresistence(iter->first);
				if (!presistencePtr->rollback(transactionId, iter->second))
				{
					flag = false;
				}
			}

			return flag;
		}

	}
}