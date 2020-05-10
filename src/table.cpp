#include "table.h"

namespace obito {
	namespace table
	{

		Column::Column(std::string theColumnName, _column_type_int theValueType, size_t theSize)
		{
			columnName = theColumnName;
			valueType = theValueType;
			size = theSize;
		}

		Column::Column(std::string initStr)
		{
			std::vector<std::string> output = obito::common::splitStr(initStr, '|');
			columnName = output[0];
			valueType = atoi(output[1].c_str());
			size = atoi(output[2].c_str());
		}

		std::string Column::toString()
		{
			std::string output = columnName + "|" + std::to_string(valueType) + "|" + std::to_string(size);
			return output;
		}

		Value::Value(std::string theValue, _column_type_int theValueType)
		{
			value = theValue;
			valueType = theValueType;
		}

		Value::Value(std::string initStr)
		{
			std::vector<std::string> output = obito::common::splitStr(initStr, '|');
			value = output[0];
			valueType = atoi(output[1].c_str());
		}

		std::string Value::toString()
		{
			std::string output = value + "|" + std::to_string(valueType);
			return output;
		}

		ValueRow::ValueRow(int theId, std::vector<Value> theValueContainer)
		{
			id = theId;
			valueContainer = theValueContainer;
		}

		ValueRow::ValueRow(std::string initStr)
		{
			std::vector<std::string> output = obito::common::splitStr(initStr, '&');
			id = atoi(output[0].c_str());
			for (int i = 1; i < output.size(); i++)
			{
				valueContainer.push_back(Value(output[i]));
			}
		}

		std::string ValueRow::toString()
		{
			std::string output = std::to_string(id);
			for (auto it = valueContainer.begin(); it < valueContainer.end(); it++)
			{
				output += "&";
				output += it->toString();
			}
			return output;
		}

		Table::Table(std::string tableName, std::vector<Column> columns)
		{
			columnVec_ = columns;
			tableFileName = obito::common::generateTableFileName(tableName);
			dataFileName = obito::common::generateDataFileName(tableName);
		}

	}
}