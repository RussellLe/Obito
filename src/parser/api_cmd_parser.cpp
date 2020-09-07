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
				std::vector<std::string> columnPair = obito::common::splitStr(words[i], VALUE_SPLIT_SYMBOL);
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

			output.tableName = words[1];
			output.id = obito::common::turnStrToInteger(words[2]);
			output.valuesOnStr = obito::common::splitStr(words[3], VALUE_SPLIT_SYMBOL);

			output.isOutput = true;
			return output;
		}

		ReadCmdParseOutput parseReadCmd(std::string command)
		{
			ReadCmdParseOutput output;
			output.isOutput = false;

			std::vector<std::string> words = obito::common::splitStr(command, WORD_SPLIT_SYMBOL);
			if (words[0] != READ_KEYWORD)
			{
				return output;
			}

			output.tableName = words[1];
			output.id = obito::common::turnStrToInteger(words[2]);

			output.isOutput = true;
			return output;
		}

		UpdateCmdParseOutput parseUpdateCmd(std::string command)
		{
			UpdateCmdParseOutput output;
			output.isOutput = false;
			
			std::vector<std::string> words = obito::common::splitStr(command, WORD_SPLIT_SYMBOL);
			if (words[0] != UPDATE_KEYWORD)
			{
				return output;
			}

			output.tableName = words[1];
			output.id = obito::common::turnStrToInteger(words[2]);
			output.valuesOnStr = obito::common::splitStr(words[3], VALUE_SPLIT_SYMBOL);
			
			output.isOutput = true;
			return output;
		}

		DeleteCmdParseOutput parseDeleteCmd(std::string command)
		{
			DeleteCmdParseOutput output;
			output.isOutput = false;

			std::vector<std::string> words = obito::common::splitStr(command, WORD_SPLIT_SYMBOL);
			if (words[0] != DELETE_KEYWORD)
			{
				return output;
			}

			output.tableName = words[1];
			output.id = obito::common::turnStrToInteger(words[2]);
			
			output.isOutput = true;
			return output;
		}

		void CreateTableParseOutput::printInfo()
		{
			std::cout << "========Create Table Parse Output Info=======" << std::endl;
			std::cout << tableName << std::endl;
			for (auto iter = columnMap.begin(); iter != columnMap.end(); iter++)
			{
				std::cout << iter->first << std::endl;
			}
			std::cout << "=============================================" << std::endl;
		}

		void AddCmdParseOutput::printInfo()
		{
			std::cout << "========Add Cmd Parse Output Info=======" << std::endl;
			std::cout << id << std::endl;
			std::cout << tableName << std::endl;
			for (auto iter = valuesOnStr.begin(); iter < valuesOnStr.end(); iter++)
			{
				std::cout << *iter << std::endl;
			}
			std::cout << "=============================================" << std::endl;
		}

	}
}