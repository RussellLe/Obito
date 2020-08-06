#pragma once
#include "../stdafx.h"
#include "../util.h"
#include "../datafield/i_data_field.h"
#include "../table.h"


typedef obito::datafield::DataFieldEnum DataFieldEnum;
typedef obito::table::Value Value;


namespace obito {
	namespace parser {


		class CreateTableParseOutput
		{
		public:
			std::string tableName;
			std::map<std::string, DataFieldEnum> columnMap;
			bool isOutput;
		};

		class AddCmdParseOutput
		{
		public:
			int id;
			std::string tableName;
			std::vector<std::string> valuesOnStr;
			bool isOutput;
		};

		CreateTableParseOutput parseCreateTable(std::string command);

		AddCmdParseOutput parseAddCmd(std::string command);

	}
}