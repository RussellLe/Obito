#pragma once
#include "stdafx.h"
#include "global.h"
#include "transaction/transaction_mgr.h"
#include "table.h"


typedef obito::global::GlobalModuleManager GlobalModuleManager;
typedef obito::transaction::TransactionManager TransactionManager;
typedef obito::table::Column Column;

namespace obito {
	namespace api {

		class ObitoApi
		{
		public:
			ObitoApi(const GlobalModuleManager& globalModuleManager);
			~ObitoApi();
			std::string exeObitoCmd(std::string command, int transactionId);

		protected:
			bool createTableByCmd(std::string command);

		protected:
			TransactionManager trxMgr_;
		};

	}
}