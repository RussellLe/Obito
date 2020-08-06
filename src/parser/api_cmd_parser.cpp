#include "api_cmd_parser.h"



namespace obito {
	namespace parser {

		CreateTableParseOutput parseCreateTable(std::string command)
		{
			CreateTableParseOutput output;
			output.isOutput = false;

			std::vector<std::string> words = obito::common::splitStr(command, WORD_SPLIT_SYMBOL);
			if (words[0] != CREATE_TABLE_KEYWORD)
			{
				return output;
			}

			output.tableName = words[1];

			for (int i = 2; i < words.size(); i++)
			{
				std::vector<std::string> columnPair = obito::common::splitStr(command, VALUE_SPLIT_SYMBOL);
				std::string columnName = columnPair[0];
				DataFieldEnum dataFieldEnum;

				if (columnPair[1] == INTEGER_FIELD_KEYWORD)
				{
					dataFieldEnum = DataFieldEnum::IntegerFieldEnum;
				}
				else if (columnPair[1] == DOUBLE_FIELD_KEYWORD)
				{
					dataFieldEnum = DataFieldEnum::DoubleFieldEnum;
				}
				else if (columnPair[1] == FLOAT_FIELD_KEYWORD)
				{
					dataFieldEnum = DataFieldEnum::FloatFieldEnum;
				}
				else if (columnPair[1] == STRING_FIELD_KEYWORD)
				{
					dataFieldEnum = DataFieldEnum::StringFieldEnum;
				}
				else
				{
					return output;
				}

				output.columnMap.insert(std::pair<std::string, DataFieldEnum>(columnName, dataFieldEnum));
			}

			output.isOutput = true;
			return output;
		}


		AddCmdParseOutput parseAddCmd(std::string command)
		{
			AddCmdParseOutput output;
			output.isOutput = false;

			std::vector<std::string> words = obito::common::splitStr(command, WORD_SPLIT_SYMBOL);
			if (words[0] != ADD_KEYWORD)
			{
				return output;
			}

			std::string tableName = words[1];
			int id = obito::common::turnStrToInteger(words[2]);
			output.valuesOnStr = obito::common::splitStr(words[3], VALUE_SPLIT_SYMBOL);

			output.isOutput = true;
			return output;
		}



	}
}