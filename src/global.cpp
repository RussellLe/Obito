#include "global.h"



namespace obito {
	namespace global {

		TablePresistenceMap::TablePresistenceMap()
		{
			tableNameFile = "TableNameFile.dat";
			loadTableNameFromFile();
		}

		TablePresistenceMap::~TablePresistenceMap()
		{
			//
		}

		bool TablePresistenceMap::addTablePresistencePair(std::string tableName, std::shared_ptr<PresistenceHandler> presistencePtr)
		{
			tablePresistenceMap_[tableName] = presistencePtr;
			return true;
		}

		bool TablePresistenceMap::checkTableExist(std::string tableName)
		{
			if (tablePresistenceMap_.find(tableName) == tablePresistenceMap_.end())
			{
				return false;
			}
			return true;
		}

		std::shared_ptr<PresistenceHandler> TablePresistenceMap::getPresistence(std::string tableName)
		{
			return tablePresistenceMap_.find(tableName)->second;
		}

		void TablePresistenceMap::syncTableNameToFile(std::vector<std::string> tableNames)
		{
			obito::file::deleteFile(tableNameFile);
			obito::file::createFile(tableNameFile);

			std::string tableNamesOnStr = "";
			for (auto iter = tableNames.begin(); iter < tableNames.end(); iter++)
			{
				tableNamesOnStr = tableNamesOnStr + (*iter) + VALUE_SPLIT_SYMBOL;
			}
			tableNamesOnStr.pop_back();

			obito::file::writeStringToFile(tableNameFile, tableNamesOnStr, 0);
			return;
		}

		void TablePresistenceMap::loadTableNameFromFile()
		{
			std::string tableNamesOnStr = obito::file::readAllStringFromFile(tableNameFile);
			std::vector<std::string> tableNames = obito::common::splitStr(tableNamesOnStr, VALUE_SPLIT_SYMBOL);
			
			for (auto iter = tableNames.begin(); iter < tableNames.end(); iter++)
			{
				std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>(*iter);
				std::shared_ptr<obito::presistence::PresistenceHandler> phptr=std::make_shared
					<obito::presistence::PresistenceHandler>(tablePtr, tablePtr->columns);
				addTablePresistencePair(*iter, phptr);
			}
			return;
		}

		bool TablePresistenceMap::flushPresistences()
		{
			std::vector<std::string> tableNames;
			for (auto iter = tablePresistenceMap_.begin(); iter != tablePresistenceMap_.end(); iter++)
			{
				if (iter->second->tablePtr_->tableName == "")
				{
					continue;
				}
				iter->second->flushBuffer_();
				iter->second->tablePtr_->syncColumnsToFile();
				tableNames.push_back(iter->second->tablePtr_->tableName);
			}
			syncTableNameToFile(tableNames);
			return true;
		}

		GlobalModuleManager::~GlobalModuleManager()
		{
			std::cout << "delete gmm" << std::endl;
			tablePresistenceMap.flushPresistences();
		}

	}
}