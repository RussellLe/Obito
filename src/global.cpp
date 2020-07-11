#include "global.h"



namespace obito {
	namespace global {

		TablePresistenceMap::TablePresistenceMap()
		{
			//
		}

		TablePresistenceMap::~TablePresistenceMap()
		{
			//
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

	}
}