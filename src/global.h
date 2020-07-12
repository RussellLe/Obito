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

		protected:
			std::map<std::string, std::shared_ptr<PresistenceHandler>> tablePresistenceMap_;

		};

		class GlobalModuleManager
		{
		public:
			TablePresistenceMap tablePresistenceMap;
		};

	}
}