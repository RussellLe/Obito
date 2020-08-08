#include "double_field.h"


namespace obito {
	namespace datafield {

		DoubleField::DoubleField()
		{
			dataFieldEnum = obito::datafield::DoubleFieldEnum;
		}

		DoubleField::DoubleField(double theValue)
		{
			dataFieldEnum = obito::datafield::DoubleFieldEnum;
			value = theValue;
		}

		DoubleField::DoubleField(char* initStr)
		{
			dataFieldEnum = obito::datafield::DoubleFieldEnum;
			memcpy(&value, initStr, sizeof(value));
		}

		DoubleField::~DoubleField()
		{
			//
		}

		size_t DoubleField::getValueSize()
		{
			return sizeof(double);
		}

		void DoubleField::printValue()
		{
			std::cout << value;
		}

		char* DoubleField::toBinary()
		{
			return reinterpret_cast<char*>(&value);
		}

		std::string DoubleField::getValueByStr()
		{
			return std::to_string(value);
		}


	}
}