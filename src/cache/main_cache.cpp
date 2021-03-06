#include "main_cache.h"


namespace obito {
	namespace cache {

		MainCache::MainCache()
		{
			idLinkMiddle = idLink.begin();
			hotEndLine_ = static_cast<int>(cacheMaxSize_ * MAIN_CACHE_HOT_RATE);
		}

		MainCache::~MainCache()
		{
			//
		}

		bool MainCache::addToCache(Row row)
		{
			dataPool.insert(std::pair<int, Row>(row.id, row));
			idLink.insert(idLinkMiddle, row.id);
			leftSlidCount_++;

			if (idLink.size() > cacheMaxSize_)
			{
				cacheEliminate_();
			}

			updateIdLinkMiddle_();
			return true;
		}

		bool MainCache::checkIdExist(int id)
		{
			if (dataPool.find(id) != dataPool.end())
			{
				return true;
			}

			return false;
		}

		Row MainCache::readFromCache(int id)
		{
			updateHotData_(id);
			return dataPool.find(id)->second;
		}

		bool MainCache::cacheEliminate_()
		{
			int eliminateId = idLink.back();
			idLink.pop_back();

			dataPool.erase(dataPool.find(eliminateId));

			leftSlidCount_++;

			updateIdLinkMiddle_();
			return true;
		}

		bool MainCache::deleteFromCache(int id)
		{
			if (checkIdExist(id))
			{
				dataPool.erase(dataPool.find(id));


				bool rightSlidFlag = false;
				for (auto iter = idLink.begin(); iter != idLink.end(); iter++)
				{
					if (size() >= 4)
					{
						if (*iter == *idLinkMiddle)
						{
							rightSlidFlag = true;
						}
					}
					if (*iter == id)
					{
						idLink.erase(iter);
						break;
					}
				}
				if (rightSlidFlag)
				{
					rightSlidCount_++;
				}

				if (size() == 0)
				{
					idLinkMiddle = idLink.begin();
				}

				return true;
			}
			return false;
		}

		bool MainCache::updateCacheRow(Row row)
		{
			if (!checkIdExist(row.id))
			{
				return false;
			}
			deleteFromCache(row.id);
			addToCache(row);
			return true;
		}

		void MainCache::updateIdLinkMiddle_()
		{
			while (leftSlidCount_ >= 2)
			{
				idLinkMiddle--;
				leftSlidCount_ -= 2;
			}
			while (rightSlidCount_ >= 2)
			{
				idLinkMiddle++;
				rightSlidCount_ -= 2;
			}
			while (hotSwapCount_ >= 2)
			{
				idLinkMiddle--;
				hotSwapCount_ -= 2;
			}
		}

		void MainCache::updateHotData_(int id)
		{
			int indexTmp = 1;
			for (auto iter = idLink.begin(); iter != idLink.end(); iter++)
			{
				if (*iter == id)
				{
					if (indexTmp <= hotEndLine_)
					{
						break;
					}
					idLink.erase(iter);
					idLink.push_front(id);
					hotSwapCount_++;
					break;
				}
				indexTmp++;
			}
			updateIdLinkMiddle_();
			return;
		}

		int MainCache::size()
		{
			return idLink.size();
		}

	}
}