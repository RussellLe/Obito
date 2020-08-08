#pragma once
#include "i_data_field.h"

namespace obito {
	namespace datafield {

		class FloatField : public IDataField
		{
		public:
			float value;

		public:
			FloatField();
			FloatField(char* initStr);	//input value binary
			FloatField(float theValue);
			~FloatField();

			size_t getValueSize();
			void printValue();
			char* toBinary();		//only value to binary
			std::string getValueByStr();

		};

	}
}