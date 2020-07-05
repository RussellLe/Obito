#pragma once
#include "../stdafx.h"
#include "../table.h"


typedef obito::table::Row Row;


namespace obito {
	namespace cache {

		class ICache
		{
		public:
			virtual bool addToCache(Row row) = 0;
			virtual bool checkIdExist(int id) = 0;
			virtual Row readFromCache(int id) = 0;
			virtual bool deleteFromCache(int id) = 0;
			virtual bool updateCacheRow(Row row) = 0;
		};


	}
}