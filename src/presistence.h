#pragma once
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/i_index.h"
#include "cache/i_cache.h"
#include "bufferpool/i_buffer_pool.h"


typedef obito::table::Row Row;
typedef obito::table::Table Table;
typedef obito::table::Column Column;
typedef obito::table::Value Value;

typedef obito::index::IIndex IIndex;
typedef obito::cache::ICache ICache;
typedef obito::buffer::IBufferPool IBufferPool;

namespace obito {
	namespace presistence {

		class PresistenceHandler
		{
		public:
			PresistenceHandler(std::shared_ptr<Table> tablePtr, std::vector<Column> columns);
			~PresistenceHandler();
			bool addRow(Row row);								//add to all
			bool writeRow(Row row);			//write to file directly
			bool writeRows(std::vector<Row> rows);			//write to file directly (used to flush buffer)
			Row readRow(int id);				//read from all
			bool deleteRow(int id);				//delete from all

		protected:
			std::shared_ptr<Table> tablePtr_;
			std::shared_ptr<IIndex> indexPtr_;
			std::shared_ptr<ICache> cachePtr_;
			std::shared_ptr<IBufferPool> bufferPtr_;
			size_t valueRowSize_;

		protected:
			bool flushBuffer_();

		};

} }