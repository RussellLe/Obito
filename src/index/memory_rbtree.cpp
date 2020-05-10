#include "memory_rbtree.h"


namespace obito {
	namespace index {

		MemoryRBTree::MemoryRBTree(std::string theIndexFileName, std::string theIndexFragFileName, size_t theValueRowSize)
		{
			dataFileoffsetCursor_ = 0;
			valueRowSize_ = theValueRowSize;
			indexFileName_ = theIndexFileName;
			indexFragFileName_ = theIndexFragFileName;

			loadIndexFromFile();
		}

		MemoryRBTree::~MemoryRBTree()
		{
			syncIndexToFile();
		}

		int MemoryRBTree::addIndexUnit(int id)
		{
			auto existIter = indexContainer_.find(id);
			if (existIter != indexContainer_.end())
			{
				return existIter->second;
			}
			if (!offsetFrags_.empty())
			{
				auto iter = offsetFrags_.end() - 1;
				int nowOffset = *iter;
				indexContainer_.insert(std::pair<int, int>(id, nowOffset));
				offsetFrags_.erase(iter);
				return nowOffset;
			}
			int nowOffset = dataFileoffsetCursor_;
			indexContainer_.insert(std::pair<int,int>(id, dataFileoffsetCursor_));
			dataFileoffsetCursor_ += valueRowSize_;
			return nowOffset;
		}

		int MemoryRBTree::getOffset(int id)
		{
			if (indexContainer_.find(id) == indexContainer_.end())
			{
				return -1;
			}
			return indexContainer_.find(id)->second;
		}

		bool MemoryRBTree::deleteIndexUnit(int id)
		{
			if (indexContainer_.find(id) == indexContainer_.end())
			{
				return false;
			}
			offsetFrags_.push_back(getOffset(id));
			indexContainer_.erase(id);
			return true;
		}

		bool MemoryRBTree::syncIndexToFile()
		{
			obito::file::deleteFile(indexFileName_);
			if (!indexContainer_.empty())
			{
				obito::file::createFile(indexFileName_);

				int offsetCursorTmp = 0;
				for (auto it = indexContainer_.begin(); it != indexContainer_.end(); it++)
				{
					obito::file::writeToFile(indexFileName_,
						reinterpret_cast<char*>(&IdOffsetUnit(it->first, it->second)),
						sizeof(IdOffsetUnit), offsetCursorTmp);
					offsetCursorTmp += sizeof(IdOffsetUnit);
				}
			}


			obito::file::deleteFile(indexFragFileName_);
			if (!offsetFrags_.empty())
			{
				obito::file::createFile(indexFragFileName_);

				int offsetCursorTmp = 0;
				for (int i = 0; i < offsetFrags_.size(); i++)
				{
					obito::file::writeToFile(indexFragFileName_,
						reinterpret_cast<char*>(&offsetFrags_[i]), sizeof(int), offsetCursorTmp);
					offsetCursorTmp += sizeof(int);
				}
			}

			return true;
		}

		bool MemoryRBTree::loadIndexFromFile()
		{
			if (obito::file::isFileExist(indexFileName_))
			{
				std::string initStdString = obito::file::readAllStringFromFile(indexFileName_);
				int totalLength = initStdString.length();

				int maxOffset = 0;

				for (int offsetCursorTmp = 0; offsetCursorTmp < totalLength; offsetCursorTmp += sizeof(IdOffsetUnit))
				{
					IdOffsetUnit* idOffsetUnit = obito::file::readObjectFromFile<IdOffsetUnit>(indexFileName_, offsetCursorTmp);
					indexContainer_.insert(std::pair<int, int>(idOffsetUnit->id, idOffsetUnit->offset));

					if (idOffsetUnit->offset > maxOffset)
					{
						maxOffset = idOffsetUnit->offset;
					}
					delete idOffsetUnit;
				}
				dataFileoffsetCursor_ = maxOffset;
			}

			if (obito::file::isFileExist(indexFragFileName_))
			{
				std::string initStdString = obito::file::readAllStringFromFile(indexFragFileName_);
				int totalLength = initStdString.length();


				for (int offsetCursorTmp = 0; offsetCursorTmp < totalLength; offsetCursorTmp += sizeof(int))
				{
					int* fragsPtr = obito::file::readObjectFromFile<int>(indexFragFileName_, offsetCursorTmp);
					offsetFrags_.push_back(*fragsPtr);
					delete fragsPtr;
				}
			}

			return true;
		}

} }