#include "presistence.h"



namespace obito {
	namespace presistence {

		PresistenceHandler::PresistenceHandler(std::string theFileName)
		{
			fileName = theFileName;
		}

		bool PresistenceHandler::writeRow(Row row)
		{
			return true;
		}

} }