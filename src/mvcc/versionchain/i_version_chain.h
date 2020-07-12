#pragma once
#include "../../stdafx.h"
#include "../../table.h"

typedef obito::table::Row Row;

namespace obito {
	namespace versionchain {


		class IVersionChain
		{
		public:
			virtual Row readRow(int id, int transactionId) = 0;
			virtual Row readPreRow(int id, int transactionId) = 0;
			virtual Row readLatestRow(int id) = 0;
			virtual bool addRow(Row row) = 0;
			virtual bool deleteRow(int id, int transactionId) = 0;

		};

	}
}