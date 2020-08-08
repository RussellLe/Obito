#pragma once
#include "i_data_field.h"


namespace obito {
	namespace datafield {

		class StringField : public IDataField
		{
		public:
			std::string value;

		public:
			StringField();
			StringField(char* initStr);	//input value binary
			StringField(std::string theValue);
			~StringField();

			size_t getValueSize();
			void printValue();
			char* toBinary();		//only value to binary
			std::string getValueByStr();

		};


	}
}