#pragma once
#include "i_data_field.h"


namespace obito {
	namespace datafield {

		class DoubleField : public IDataField
		{
		public:
			double value;

		public:
			DoubleField();
			DoubleField(char* initStr);	//input value binary
			DoubleField(double theValue);
			~DoubleField();

			size_t getValueSize();
			void printValue();
			char* toBinary();		//only value to binary


		};


	}
}