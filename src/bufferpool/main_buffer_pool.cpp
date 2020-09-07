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
			std::cout << "add " << row.id << " to buffer pool" << std::endl;
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

		bool MainBufferPool::deleteFromBuffer(int id)
		{
			dataPool.erase(id);
			return true;
		}

		std::vector<Row> MainBufferPool::getRowsFromBuffer()
		{
			std::vector<Row> rows;
			for (auto iter = dataPool.begin(); iter != dataPool.end(); iter++)
			{
				rows.push_back(iter->second);
			}
			return rows;
		}

		bool MainBufferPool::cleanBuffer()
		{
			dataPool.clear();
			return true;
		}

		bool MainBufferPool::getFlushStatus()
		{
			return flushFlag;
		}

	}
}