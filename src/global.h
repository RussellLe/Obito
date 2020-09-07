#pragma once
#include "stdafx.h"
#include "presistence.h"


typedef obito::presistence::PresistenceHandler PresistenceHandler;

namespace obito {
	namespace global {

		class TablePresistenceMap
		{
		public:
			TablePresistenceMap();
			~TablePresistenceMap();
			bool addTablePresistencePair(std::string tableName,std::shared_ptr<PresistenceHandler> presistencePtr);
			bool checkTableExist(std::string tableName);
			std::shared_ptr<PresistenceHandler> getPresistence(std::string tableName);


			bool flushPresistences();
			

		protected:
			std::map<std::string, std::shared_ptr<PresistenceHandler>> tablePresistenceMap_;
			std::string tableNameFile;

		protected:
			void syncTableNameToFile(std::vector<std::string> tableNames);
			void loadTableNameFromFile();

		};

		class GlobalModuleManager
		{
		public:
			~GlobalModuleManager();
			TablePresistenceMap tablePresistenceMap;
		};

	}
}