#pragma once
#include "i_cache.h"


namespace obito {
	namespace cache {

		class MainCache : public ICache
		{
		public:
			std::map<int, Row> dataPool;
			std::list<int> idLink;
			std::list<int>::iterator idLinkMiddle;

		public:
			MainCache();
			~MainCache();
			bool addToCache(Row row);
			bool checkIdExist(int id);
			Row readFromCache(int id);
			bool deleteFromCache(int id);
			bool updateCacheRow(Row row);

			int size();

		protected:
			bool cacheEliminate_();
			void updateIdLinkMiddle_();
			void updateHotData_(int id);

		private:
			int cacheMaxSize_ = MAIN_CACHE_MAX_SIZE;
			int rightSlidCount_ = 0;
			int leftSlidCount_ = 0;
			int hotSwapCount_ = 0;

			int hotEndLine_ = 0;

		};

	}
}