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
			int begin(std::string tableName);
			bool commit(int transactionId);
			bool rollback(int transactionId);

			bool addRow(int transactionId, Row row);
			Row readRow(int transactionId, int rowId);
			bool deleteRow(int transacitonId, int rowId);
			bool updateRow(int transactionId, Row row);

		protected:
			GlobalModuleManager globalModuleManager_;

			int transactionIdCursor_;
			std::map<int, TransactionObject> transactionPool_;

		};


	}
}