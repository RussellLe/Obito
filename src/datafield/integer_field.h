#pragma once
#include "i_data_field.h"



namespace obito {
	namespace datafield {

		class IntegerField : public IDataField
		{
		public:
			int value;
			

		public:
			IntegerField();
			IntegerField(char* initStr);	//input value binary
			IntegerField(int theValue);
			~IntegerField();

			size_t getValueSize();
			void printValue();
			char* toBinary();		//only value to binary

		};

} }