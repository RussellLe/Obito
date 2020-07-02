#include "main_buffer_pool.h"




namespace obito {
	namespace buffer {

		MainBufferPool::MainBufferPool()
		{
			poolMaxSize_ = MAIN_BUFFER_POOL_SIZE;
			flushFlag = false;
		}

		bool MainBufferPool::addToBuffer(Row row)
		{
			dataPool.insert(std::pair<int, Row>(row.id, row));
			updateFlushFlag();
			return true;
		}

		void MainBufferPool::updateFlushFlag()
		{
			if (!flushFlag && dataPool.size() >= poolMaxSize_)
			{
				flushFlag = true;
			}
			else if (flushFlag && dataPool.size() < poolMaxSize_)
			{
				flushFlag = false;
			}
			
			return;
		}

		bool MainBufferPool::checkIdExist(int id)
		{
			if (dataPool.find(id) != dataPool.end())
			{
				return true;
			}
			return false;
		}

		Row MainBufferPool::readFromBuffer(int id)
		{
			return dataPool.find(id)->second;
		}

	}
}