#include "transaction_mgr.h"


namespace obito {
	namespace transaction {

		TransactionManager::TransactionManager(const GlobalModuleManager& globalModuleManager)
		{
			globalModuleManager_ = globalModuleManager;
			transactionIdCursor_ = 1;
			isolationLevel = MEDIUM_ISOLATION_LEVEL;
			rightEndTransactionId = 0;
		}

		TransactionManager::~TransactionManager()
		{
			//
		}

		bool TransactionManager::setIsolationLevel(TransactionIsolationLevel theIsolationLevel)
		{
			isolationLevel = theIsolationLevel;
			return true;
		}

		int TransactionManager::begin()
		{
			int transactionId = transactionIdCursor_;
			transactionIdCursor_++;

			transactionPool_.insert(std::pair<int, TransactionObject>(transactionId, 
				*(new TransactionObject(transactionId, rightEndTransactionId, isolationLevel, globalModuleManager_.tablePresistenceMap))));
			
			return transactionId;
		}

		bool TransactionManager::commit(int transactionId)
		{
			if (transactionId > rightEndTransactionId)
			{
				rightEndTransactionId = transactionId;
			}
			transactionPool_.erase(transactionId);
			return true;
		}

		bool TransactionManager::rollback(int transactionId)
		{
			return transactionPool_.find(transactionId)->second.rollback();
		}

		bool TransactionManager::addRow(int transactionId, std::string tableName, Row row)
		{
			auto transactionIter = transactionPool_.find(transactionId);
			if (transactionIter == transactionPool_.end())
			{
				return false;
			}

			return transactionIter->second.addRow(tableName, row);
		}

		Row TransactionManager::readRow(int transactionId, std::string tableName, int rowId)
		{
			auto transactionIter = transactionPool_.find(transactionId);
			if (transactionIter == transactionPool_.end())
			{
				Row errorRow;
				errorRow.id = ERROR_ROW_FLAG;
				errorRow.transactionId = ERROR_ROW_FLAG;
				return errorRow;
			}

			return transactionIter->second.readRow(tableName, rowId, rightEndTransactionId);
		}

		bool TransactionManager::deleteRow(int transactionId, std::string tableName, int rowId)
		{
			auto transactionIter = transactionPool_.find(transactionId);
			if (transactionIter == transactionPool_.end())
			{
				return false;
			}

			return transactionIter->second.deleteRow(tableName, rowId);
		}

		bool TransactionManager::updateRow(int transactionId, std::string tableName, Row row)
		{
			auto transactionIter = transactionPool_.find(transactionId);
			if (transactionIter == transactionPool_.end())
			{
				return false;
			}

			return transactionIter->second.updateRow(tableName, row);
		}

		bool TransactionManager::checkTransactionExist(int transactionId)
		{
			if (transactionPool_.find(transactionId) == transactionPool_.end())
			{
				return false;
			}
			return true;
		}

	}
}