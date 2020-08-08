#pragma once

#include "../stdafx.h"
#include  "../util.h"


namespace obito {
	namespace datafield {

		enum DataFieldEnum
		{
			StringFieldEnum = 1,
			IntegerFieldEnum = 2,
			FloatFieldEnum = 3,
			DoubleFieldEnum = 4
		};

		class IDataField
		{
		public:
			DataFieldEnum dataFieldEnum;
			
		public:
			virtual ~IDataField() {}
			virtual size_t getValueSize() = 0;
			virtual void printValue() = 0;
			virtual char* toBinary() = 0;
			virtual std::string getValueByStr() = 0;

		};

} }