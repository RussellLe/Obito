#pragma once
#include "i_buffer_pool.h"
#include "../presistence.h"


typedef obito::presistence::PresistenceHandler PresistenceHandler;

namespace obito {
	namespace buffer {

		class MainBufferPool :public IBufferPool
		{
		public:
			MainBufferPool();
			bool addToBuffer(Row row);
			void updateFlushFlag();
			bool checkIdExist(int id);
			Row readFromBuffer(int id);

			std::vector<Row> getRowsFromBuffer();
			bool cleanBuffer();
			bool getFlushStatus();

		public:
			std::map<int, Row> dataPool;
			bool flushFlag = false;

		private:
			int poolMaxSize_ = 0;

		};


	}
}