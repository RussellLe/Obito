#include "api.h"


namespace obito {
	namespace api {

		ObitoApi::ObitoApi(const GlobalModuleManager& globalModuleManager)
			: trxMgr_(globalModuleManager)
		{
			//
		}

		ObitoApi::~ObitoApi()
		{
			//
		}

		std::string ObitoApi::exeObitoCmd(std::string command, int transactionId)
		{
			return "success";
		}

		bool ObitoApi::createTableByCmd(std::string command)
		{
			std::vector<Column> columns;
			return true;
		}

	}
}