#include "main_cache.h"


namespace obito {
	namespace cache {

		MainCache::MainCache()
		{
			idLinkMiddle = idLink.begin();
			hotEndLine_ = static_cast<int>(cacheMaxSize_ * MAIN_CACHE_HOT_RATE);
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
			for (auto iter = idLink.begin(); iter != idLink.end(); iter++)
			{
				if (*iter == id)
				{
					return true;
				}
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

			rightSlidCount_++;

			updateIdLinkMiddle_();
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
				idLinkMiddle--;
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

	}
}