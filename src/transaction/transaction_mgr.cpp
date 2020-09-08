#include "transaction_mgr.h"


namespace obito {
	namespace transaction {

		TransactionManager::TransactionManager(const GlobalModuleManager& globalModuleManager)
		{
			globalModuleManager_ = globalModuleManager;
			isolationLevel = MEDIUM_ISOLATION_LEVEL;

			trxIdFileName_ = "trxId.dat";
			loadTrxIdCursor();
		}

		TransactionManager::~TransactionManager()
		{
			syncTrxIdCursor();
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

		void TransactionManager::syncTrxIdCursor()
		{
			obito::file::deleteFile(trxIdFileName_);
			obito::file::createFile(trxIdFileName_);
			obito::file::writeStringToFile(trxIdFileName_, std::to_string(transactionIdCursor_) 
				+ VALUE_SPLIT_SYMBOL + std::to_string(rightEndTransactionId), 0);
		}

		void TransactionManager::loadTrxIdCursor()
		{
			std::string originStr = obito::file::readAllStringFromFile(trxIdFileName_); 
				std::vector<std::string> output = obito::common::splitStr(originStr, VALUE_SPLIT_SYMBOL);
			transactionIdCursor_ = std::stoi(output[0]);
			rightEndTransactionId = std::stoi(output[1]);
			std::cout << "load trxidcursor:" << transactionIdCursor_ << std::endl;
			std::cout << "load rightend:" << rightEndTransactionId << std::endl;
		}

	}
}