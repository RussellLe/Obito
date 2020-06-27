#pragma once
#include "i_index.h"



namespace obito {
	namespace index {

		class MemoryRBTree : public MemoryIndex
		{
		public:
			MemoryRBTree(std::string theIndexFileName, std::string theIndexFragFileName, size_t theValueRowSize);
			~MemoryRBTree();
			int addIndexUnit(int id);
			int getOffset(int id);
			bool deleteIndexUnit(int id);

		protected:
			std::map<int, int> indexContainer_;
			std::vector<int> offsetFrags_;
			int dataFileoffsetCursor_;

		protected:
			bool syncIndexToFile();
			bool loadIndexFromFile();

		private:
			void printIndexContainer_();

		};

} }