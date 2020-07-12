#pragma once
#include "../stdafx.h"
#include "transaction_obj.h"
#include "../presistence.h"
#include "../global.h"


typedef obito::presistence::PresistenceHandler PresistenceHandler;
typedef obito::global::GlobalModuleManager GlobalModuleManager;

namespace obito {
	namespace transaction {


		class TransactionManager
		{
		public:
			TransactionManager(const GlobalModuleManager& globalModuleManager);
			~TransactionManager();
			int begin();
			bool commit(int transactionId);
			bool rollback(int transactionId);

			bool addRow(int transactionId, std::string tableName, Row row);
			Row readRow(int transactionId, std::string tableName, int rowId);
			bool deleteRow(int transactionId, std::string tableName, int rowId);
			bool updateRow(int transactionId, std::string tableName, Row row);

			bool setIsolationLevel(TransactionIsolationLevel theIsolationLevel);

			bool checkTransactionExist(int transactionId);

		public:
			TransactionIsolationLevel isolationLevel;
			int rightEndTransactionId;	//latest commit transaction id

		protected:
			GlobalModuleManager globalModuleManager_;

			int transactionIdCursor_;
			std::map<int, TransactionObject> transactionPool_;

		};


	}
}