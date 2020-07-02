#pragma once
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/i_index.h"


typedef obito::table::Row Row;
typedef obito::table::Table Table;
typedef obito::table::Column Column;
typedef obito::table::Value Value;
typedef obito::index::IIndex IIndex;

namespace obito {
	namespace presistence {

		class PresistenceHandler
		{
		public:
			PresistenceHandler(std::shared_ptr<Table> tablePtr, std::vector<Column> columns);
			bool writeRow(int id, std::vector<Value> values);
			bool writeRow(int id, Row row);
			Row readRow(int id);
			bool deleteRow(int id);

		protected:
			std::shared_ptr<Table> tablePtr_;
			std::shared_ptr<IIndex> indexPtr_;
			size_t valueRowSize_;

		};

} }