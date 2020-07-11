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


		class TransactionObject
		{
		public:
			int transactionId;
			
		public:
			TransactionObject(int theTransactionId, const TablePresistenceMap& tablePresistenceMap);
			~TransactionObject();
			bool addRow(std::string tableName, Row row);
			Row readRow(std::string tableName, int id);
			bool deleteRow(std::string tableName, int id);
			bool updateRow(std::string tableName, Row row);
			
		protected:
			TablePresistenceMap tablePresistenceMap_;

		};

	}
}