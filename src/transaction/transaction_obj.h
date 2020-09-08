#pragma once
#include "../stdafx.h"
#include "../presistence.h"
#include "../table.h"
#include "../global.h"

typedef obito::presistence::PresistenceHandler PresistenceHandler;
typedef obito::table::Row Row;
typedef obito::global::TablePresistenceMap TablePresistenceMap;

namespace obito {
	namespace transaction {

		enum TransactionIsolationLevel
		{
			LOW_ISOLATION_LEVEL = 1,	//read uncommitted
			MEDIUM_ISOLATION_LEVEL = 2,	//read committed
			HIGH_ISOLATION_LEVEL = 3	//read begin
		};

		class TransactionObject
		{
		public:
			int transactionId;
			
		public:
			TransactionObject(int theTransactionId, int theLeftEndTransactionId, TransactionIsolationLevel isolationLevel,
				TablePresistenceMap& tablePresistenceMap);
			~TransactionObject();
			bool addRow(std::string tableName, Row row);
			Row readRow(std::string tableName, int id, int rightEndTransactionId);
			bool deleteRow(std::string tableName, int id);
			bool updateRow(std::string tableName, Row row);
			bool rollback();
			
		public:
			int leftEndTransactionId;	//latest commit transaction id when begin
			std::map<std::string,std::vector<int>> updateIdMap_;

		protected:
			TablePresistenceMap& tablePresistenceMap_;
			TransactionIsolationLevel isolationLevel_;

		};

	}
}