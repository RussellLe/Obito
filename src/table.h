#pragma once
#include "stdafx.h"
#include "util.h"
#include "datafield/i_data_field.h"


typedef obito::datafield::DataFieldEnum DataFieldEnum;
typedef obito::datafield::IDataField IDataField;

namespace obito {
	namespace table
	{
		
		class Value
		{
		public:
			std::shared_ptr<IDataField> valuePtr;
			size_t valueSize;

		public:
			Value(){}
			Value(DataFieldEnum dataFieldEnum, char* initStr);
			Value(std::shared_ptr<IDataField> theValuePtr);
			void printValue();
		};

		class Column
		{
		public:
			std::string columnName;
			DataFieldEnum valueType;
			Column() {}
			Column(char* initStr);
			Column(std::string theColumnName, DataFieldEnum theValueType);
			char* toBinary();
		};

		class Table
		{
		public:
			std::string tableName;
			std::vector<Column> columns;
			Table() {}
			Table(std::string theTableName);
			Table(std::string theTableName, std::vector<Column> theColumns);

		public:
			void addColumn(Column theColumn);
			void syncColumnsToFile();
			void loadColumnsFromFile();

		protected:
			std::string infoFileName_;
			std::string dataFileName_;
			std::string columnsFileName_;

		};

		class Row
		{
		public:
			int id;
			std::vector<Value> values;
			size_t rowSize;
			
		protected:
			std::shared_ptr<Table> belongTablePtr;

		public:
			Row(){}
			Row(std::shared_ptr<Table> belongTable, char* initStr);
			Row(std::shared_ptr<Table> belongTable, int theId, std::vector<Value> theValues);
			void printRow();
			char* toBinary();
		};

	}
}