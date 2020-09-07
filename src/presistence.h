#pragma once
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/i_index.h"
#include "cache/i_cache.h"
#include "bufferpool/i_buffer_pool.h"
#include "mvcc/versionchain/i_version_chain.h"


typedef obito::table::Row Row;
typedef obito::table::Table Table;
typedef obito::table::Column Column;
typedef obito::table::Value Value;

typedef obito::index::IIndex IIndex;
typedef obito::cache::ICache ICache;
typedef obito::buffer::IBufferPool IBufferPool;
typedef obito::versionchain::IVersionChain IVersionChain;
typedef obito::datafield::DataFieldEnum DataFieldEnum;

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
			Row readVersionChain(int id, int transactionId);
			bool deleteRow(int id, int transactionId);				//delete from all
			bool updateRow(Row row);
			bool rollback(int transactionId, std::vector<int> updateIdVec);

			std::vector<DataFieldEnum> getColumnsDataFields();
			bool flushBuffer_();

		public:
			std::shared_ptr<Table> tablePtr_;

		protected:
			std::shared_ptr<IIndex> indexPtr_;
			std::shared_ptr<ICache> cachePtr_;
			std::shared_ptr<IBufferPool> bufferPtr_;
			std::shared_ptr<IVersionChain> versionChainPtr_;
			size_t valueRowSize_;

		protected:
			bool addRow_(Row row);
			bool deleteRow_(int id);

		};

} }