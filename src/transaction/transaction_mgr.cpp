#include "transaction_mgr.h"


namespace obito {
	namespace transaction {

		TransactionManager::TransactionManager(const GlobalModuleManager& globalModuleManager)
		{
			globalModuleManager_ = globalModuleManager;
			transactionIdCursor_ = 1;
		}

		TransactionManager::~TransactionManager()
		{
			//
		}

		int TransactionManager::begin(std::string tableName)
		{
			int transactionId = transactionIdCursor_;
			transactionIdCursor_++;

			TransactionObject transactionObject(transactionId, globalModuleManager_.tablePresistenceMap);
			transactionPool_.insert(std::pair<int, TransactionObject>(transactionIdCursor_, transactionObject));
			
			return transactionId;
		}


	}
}