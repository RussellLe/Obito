#pragma once
#include "stdafx.h"
#include "global.h"
#include "transaction/transaction_mgr.h"
#include "table.h"
#include "util.h"
#include "parser/api_cmd_parser.h"
#include "datafield/integer_field.h"
#include "datafield/float_field.h"
#include "datafield/double_field.h"
#include "datafield/string_field.h"


typedef obito::global::GlobalModuleManager GlobalModuleManager;
typedef obito::transaction::TransactionManager TransactionManager;
typedef obito::table::Column Column;

typedef obito::parser::CreateTableParseOutput CreateTableParseOutput;
typedef obito::parser::AddCmdParseOutput AddCmdParseOutput;
typedef obito::parser::ReadCmdParseOutput ReadCmdParseOutput;
typedef obito::parser::UpdateCmdParseOutput UpdateCmdParseOutput;
typedef obito::parser::DeleteCmdParseOutput DeleteCmdParseOutput;

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
			bool addByCmd(std::string command, int transactionId);
			Row readByCmd(std::string command, int transactionId);
			bool updateByCmd(std::string command, int transactionId);
			bool deleteByCmd(std::string command, int transactionId);

		protected:
			TransactionManager trxMgr_;
		};

	}
}