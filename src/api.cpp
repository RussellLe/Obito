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
			std::vector<std::string> words = obito::common::splitStr(command, VALUE_SPLIT_SYMBOL);
			bool flag = false;

			if (words[0] == CREATE_TABLE_KEYWORD)
			{
				flag = createTableByCmd(command);
			}
			else if (words[0] == ADD_KEYWORD)
			{
				flag = addByCmd(command, transactionId);
			}
			else if (words[0] == UPDATE_KEYWORD)
			{
				flag = updateByCmd(command, transactionId);
			}
			else if (words[0] == DELETE_KEYWORD)
			{
				flag = deleteByCmd(command, transactionId);
			}
			else if (words[0] == READ_KEYWORD)
			{
				Row row = readByCmd(command, transactionId);
				if (row.id != ERROR_ROW_FLAG)
				{
					flag = true;
					return row.getRowByStr();
				}
			}
			else
			{
				return "error command";
			}
			
			if (!flag)
			{
				return "failed";
			}

			return "success";
		}

		bool ObitoApi::createTableByCmd(std::string command)
		{
			CreateTableParseOutput output = obito::parser::parseCreateTable(command);
			if (output.isOutput == false)
			{
				return false;
			}

			std::vector<Column> columns;
			for (auto iter = output.columnMap.begin(); iter != output.columnMap.end(); iter++)
			{
				columns.push_back(*(new Column(iter->first,iter->second)));
			}

			std::shared_ptr<Table> tablePtr = std::make_shared<Table>(output.tableName);
			std::shared_ptr<PresistenceHandler> presistencePtr = std::make_shared<PresistenceHandler>(tablePtr, columns);
			trxMgr_.globalModuleManager_.tablePresistenceMap.addTablePresistencePair(output.tableName, presistencePtr);

			return true;
		}

		bool ObitoApi::addByCmd(std::string command, int transactionId)
		{
			AddCmdParseOutput output = obito::parser::parseAddCmd(command); 
			
			auto presistencePtr = trxMgr_.globalModuleManager_.tablePresistenceMap.getPresistence(output.tableName);
			std::vector<DataFieldEnum> dataFieldVec = presistencePtr->getColumnsDataFields();
			
			if (output.valuesOnStr.size() != dataFieldVec.size())
			{
				return false;
			}

			std::vector<Value> values;
			for (int i = 0; i < output.valuesOnStr.size(); i++)
			{
				switch (dataFieldVec[0])
				{
				case DataFieldEnum::IntegerFieldEnum: {
					int integerValue = obito::common::turnStrToInteger(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::IntegerField>(integerValue))));
					break;
				}
				case DataFieldEnum::DoubleFieldEnum: {
					double doubleValue = obito::common::turnStrToDouble(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::DoubleField>(doubleValue))));
					break;
				}
				case DataFieldEnum::FloatFieldEnum: {
					float floatValue = obito::common::turnStrToFloat(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::FloatField>(floatValue))));
					break;
				}
				case DataFieldEnum::StringFieldEnum: {
					std::string stringValue = output.valuesOnStr[i];
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::StringField>(stringValue))));
					break;
				}
				default:
					return false;
				}
			}

			Row row(presistencePtr->tablePtr_, output.id, values);
			return trxMgr_.addRow(transactionId, output.tableName, row);
		}


		Row ObitoApi::readByCmd(std::string command, int transactionId)
		{
			ReadCmdParseOutput output = obito::parser::parseReadCmd(command);
			Row row = trxMgr_.readRow(transactionId, output.tableName, output.id);
			return row;
		}

		bool ObitoApi::updateByCmd(std::string command, int transactionId)
		{
			UpdateCmdParseOutput output = obito::parser::parseUpdateCmd(command);

			auto presistencePtr = trxMgr_.globalModuleManager_.tablePresistenceMap.getPresistence(output.tableName);
			std::vector<DataFieldEnum> dataFieldVec = presistencePtr->getColumnsDataFields();

			if (output.valuesOnStr.size() != dataFieldVec.size())
			{
				return false;
			}

			std::vector<Value> values;
			for (int i = 0; i < output.valuesOnStr.size(); i++)
			{
				switch (dataFieldVec[0])
				{
				case DataFieldEnum::IntegerFieldEnum: {
					int integerValue = obito::common::turnStrToInteger(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::IntegerField>(integerValue))));
					break;
				}
				case DataFieldEnum::DoubleFieldEnum: {
					double doubleValue = obito::common::turnStrToDouble(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::DoubleField>(doubleValue))));
					break;
				}
				case DataFieldEnum::FloatFieldEnum: {
					float floatValue = obito::common::turnStrToFloat(output.valuesOnStr[i]);
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::FloatField>(floatValue))));
					break;
				}
				case DataFieldEnum::StringFieldEnum: {
					std::string stringValue = output.valuesOnStr[i];
					values.push_back(*(std::make_shared<Value>(std::make_shared<obito::datafield::StringField>(stringValue))));
					break;
				}
				default:
					return false;
				}
			}

			Row row(presistencePtr->tablePtr_, output.id, values);

			trxMgr_.updateRow(transactionId, output.tableName, row);
			return true;
		}

		bool ObitoApi::deleteByCmd(std::string command, int transactionId)
		{
			DeleteCmdParseOutput output = obito::parser::parseDeleteCmd(command);
			return trxMgr_.deleteRow(transactionId, output.tableName, output.id);
		}

	}
}