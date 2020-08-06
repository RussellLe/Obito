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

	}
}