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

		Table::Table(std::string tableName, std::vector<Column> columns)
		{
			columnVec_ = columns;
			tableFileName = obito::common::generateTableFileName(tableName);
			dataFileName = obito::common::generateDataFileName(tableName);
		}

	}
}