#include "main_version_chain.h"



namespace obito {
	namespace versionchain
	{
		MainVersionChain::MainVersionChain()
		{
			//
		}

		MainVersionChain::~MainVersionChain()
		{
			//
		}

		bool MainVersionChain::addRow(Row row)
		{
			if (versionChainMap_.find(row.id) == versionChainMap_.end())
			{
				auto histroyDataList = std::make_shared<std::list<std::pair<int, Row>>>();
				versionChainMap_[row.id] = histroyDataList;
			}

			auto idIter = versionChainMap_.find(row.id);
			auto histroyDataListPtr = idIter->second;

			if (histroyDataListPtr->empty() || histroyDataListPtr->back().first < row.transactionId)
			{
				histroyDataListPtr->push_back(std::pair<int, Row>(row.transactionId, row));
				return true;
			}

			for (auto insertIter = histroyDataListPtr->begin(); insertIter != histroyDataListPtr->end(); insertIter++)
			{
				if (insertIter->first > row.transactionId)
				{
					histroyDataListPtr->insert(insertIter, std::pair<int, Row>(row.transactionId, row));
					return true;
				}
			}

			return true;
		}

		Row MainVersionChain::readRow(int id, int transactionId)
		{
			Row errorRow;
			errorRow.id = ERROR_ROW_FLAG;

			auto idIter = versionChainMap_.find(id);
			if (idIter == versionChainMap_.end())
			{
				return errorRow;
			}

			auto histroyDataPtr = idIter->second;
			for (auto readIter = histroyDataPtr->begin(); readIter != histroyDataPtr->end(); readIter++)
			{
				if (readIter->first == transactionId)
				{
					return readIter->second;
				}
			}

			return errorRow;
		}

		Row MainVersionChain::readPreRow(int id, int transactionId)
		{
			Row errorRow;
			errorRow.id = ERROR_ROW_FLAG;

			auto idIter = versionChainMap_.find(id);
			if (idIter == versionChainMap_.end())
			{
				return errorRow;
			}

			auto histroyDataPtr = idIter->second;
			for (auto readIter = histroyDataPtr->begin(); readIter != histroyDataPtr->end(); readIter++)
			{
				if (readIter->first == transactionId)
				{
					return (--readIter)->second;
				}
			}

			return errorRow;
		}

		Row MainVersionChain::readLatestRow(int id)
		{
			Row errorRow;
			errorRow.id = ERROR_ROW_FLAG;

			auto idIter = versionChainMap_.find(id);
			if (idIter == versionChainMap_.end())
			{
				return errorRow;
			}

			auto histroyDataPtr = idIter->second;
			return histroyDataPtr->back().second;
		}

		bool MainVersionChain::deleteRow(int id, int transactionId)
		{
			auto idIter = versionChainMap_.find(id);
			if (idIter == versionChainMap_.end())
			{
				return false;
			}
			
			auto histroyDataListPtr = idIter->second;
			for (auto deleteIter = histroyDataListPtr->begin(); deleteIter != histroyDataListPtr->end(); deleteIter++)
			{
				if (deleteIter->first == transactionId)
				{
					histroyDataListPtr->erase(deleteIter);
					return true;
				}
			}
			
			return false;
		}

	}
}