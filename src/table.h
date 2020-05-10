#pragma once
#include "stdafx.h"
#include "util.h"

namespace obito {
	namespace table
	{
		class Column
		{
		public:
			std::string columnName;
			_column_type_int valueType;
			size_t size;

		public:
			Column(std::string theColumnName, _column_type_int theValueType, size_t theSize);
			Column(std::string initStr);
			std::string toString();
		};

		class Value
		{
		public:
			std::string value;
			_column_type_int valueType;

		public:
			Value(std::string theValue, _column_type_int theValueType);
			Value(std::string initStr);
			std::string toString();
		};

		class ValueRow
		{
		public:
			int id;
			std::vector<Value> valueContainer;
			ValueRow(int theId, std::vector<Value> theValueContainer);
			ValueRow(std::string initStr);
			std::string toString();
		};

		class Table
		{
		public:
			std::string tableName;
			std::string tableFileName;		//save table info(include column info)
			std::string dataFileName;		//save value row

		protected:
			std::vector<Column> columnVec_;

		public:
			Table(std::string tableName, std::vector<Column> columns);
		};
	}
}