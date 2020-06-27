#include "table.h"

#include "datafield/integer_field.h"
#include "datafield/srv_datafield.h"
#include "datafield/string_field.h"

namespace obito {
	namespace table
	{

		Value::Value(std::shared_ptr<IDataField> theValuePtr)
		{
			valuePtr = theValuePtr;
			valueSize = theValuePtr->getValueSize();
		}

		Value::Value(DataFieldEnum dataFieldEnum, char* initStr)
		{
			switch (dataFieldEnum)
			{
			case obito::datafield::IntegerFieldEnum:
				valuePtr = std::make_shared<obito::datafield::IntegerField>(initStr);
				break;
			case obito::datafield::StringFieldEnum:
				valuePtr = std::make_shared<obito::datafield::StringField>(initStr);
			default:
				break;
			}
			valueSize = valuePtr->getValueSize();
		}

		void Value::printValue()
		{
			valuePtr->printValue();
		}

		Row::Row(std::shared_ptr<Table> belongTable, int theId, std::vector<Value> theValues)
		{
			belongTablePtr = belongTable;

			id = theId;
			values = theValues;
			rowSize = 0;
			for (auto iter = values.begin(); iter < values.end(); iter++)
			{
				rowSize += iter->valueSize;
			}
		}

		Row::Row(std::shared_ptr<Table> belongTable, char* initStr)		//Binary row length: sizeof(int)+sizeof(size_t)+rowSize
		{
			belongTablePtr = belongTable;

			memcpy(&id, initStr, sizeof(int));
			memcpy(&rowSize, initStr + sizeof(int), sizeof(size_t));

			int offsetCursor = sizeof(int) + sizeof(size_t);
			int totalSize = rowSize + offsetCursor;

			for (auto iter = belongTablePtr->columns.begin(); iter < belongTablePtr->columns.end(); iter++)
			{
				Value valueObj(iter->valueType, initStr + offsetCursor);
				values.push_back(valueObj);
				offsetCursor += valueObj.valuePtr->getValueSize();
			}
		}

		void Row::printRow()
		{
			std::cout << id << ' ';
			for (auto iter = values.begin(); iter < values.end(); iter++)
			{
				iter->printValue();
				std::cout << ' ';
			}
			std::cout << std::endl;
		}

		char* Row::toBinary()
		{
			char* output = (char*)malloc(sizeof(id) + sizeof(rowSize) + rowSize);

			char* idStr = reinterpret_cast<char*>(&id);
			char* sizeStr =  reinterpret_cast<char*>(&rowSize);


			memcpy(output, idStr, sizeof(id));
			memcpy(output + sizeof(id), sizeStr, sizeof(rowSize));

			int offsetCursor = sizeof(id) + sizeof(rowSize);
			for (auto iter = values.begin(); iter < values.end(); iter++)
			{
				memcpy(output + offsetCursor, iter->valuePtr->toBinary(), iter->valuePtr->getValueSize());
				offsetCursor += iter->valuePtr->getValueSize();
			}
			return output;
		}

		size_t Row::getValueRowSize()
		{
			return sizeof(int) + sizeof(size_t) + rowSize;
		}

		Column::Column(std::string theColumnName, DataFieldEnum theValueType)
		{
			columnName = theColumnName;
			valueType = theValueType;
		}

		Column::Column(char* initStr)
		{
			memcpy(this, initStr, sizeof(Column));
		}

		char* Column::toBinary()
		{
			return reinterpret_cast<char*>(this);
		}

		size_t Column::getValueSize()
		{
			return obito::datafield::getValueSizeByDFE(valueType);
		}

		void Table::checkTableFile_()
		{
			if (!obito::file::isFileExist(infoFileName_))
			{
				obito::file::createFile(infoFileName_);
			}
			if (!obito::file::isFileExist(dataFileName_))
			{
				obito::file::createFile(dataFileName_);
			}
			if (!obito::file::isFileExist(columnsFileName_))
			{
				obito::file::createFile(columnsFileName_);
			}
		}

		Table::Table(std::string theTableName)
		{
			tableName = theTableName;
			infoFileName_ = obito::common::generateTableInfoFileName(tableName);
			dataFileName_ = obito::common::generateTableDataFileName(tableName);
			columnsFileName_ = obito::common::generateColumnsFileName(tableName);

			checkTableFile_();
		}

		Table::Table(std::string theTableName, std::vector<Column> theColumns)
		{
			tableName = theTableName;
			infoFileName_ = obito::common::generateTableInfoFileName(tableName);
			dataFileName_ = obito::common::generateTableDataFileName(tableName);
			columnsFileName_ = obito::common::generateColumnsFileName(tableName);

			checkTableFile_();
		}

		void Table::addColumn(Column theColumn)
		{
			columns.push_back(theColumn);
		}

		void Table::syncColumnsToFile()
		{
			obito::file::createFile(columnsFileName_);
			int offsetCursor = 0;
			for (auto iter = columns.begin(); iter < columns.end(); iter++)
			{
				obito::file::writeToFile(columnsFileName_, iter->toBinary(), sizeof(Column), offsetCursor);
				offsetCursor += sizeof(Column);
			}
		}

		void Table::loadColumnsFromFile()
		{
			std::string tmp = obito::file::readAllStringFromFile(columnsFileName_);
			int length = tmp.length();

			char* initColumnsStr = obito::file::turnStdStringToBinary(tmp);
			
			for (int offsetCursor = 0; offsetCursor < length; offsetCursor += sizeof(Column))
			{
				Column columnObj(initColumnsStr + offsetCursor);
				columns.push_back(columnObj);
			}
		}

		std::string Table::getDataFileName()
		{
			return dataFileName_;
		}

		size_t Table::getValueRowSize()
		{
			size_t output = sizeof(int) + sizeof(size_t);
			for (auto iter = columns.begin(); iter < columns.end(); iter++)
			{
				output += iter->getValueSize();
			}
			return output;
		}
	}
}