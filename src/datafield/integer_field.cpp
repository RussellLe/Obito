#include "integer_field.h"


namespace obito {
	namespace datafield {
		
		IntegerField::IntegerField()
		{
			dataFieldEnum = obito::datafield::IntegerFieldEnum;
		}

		IntegerField::IntegerField(char* initStr)
		{
			dataFieldEnum = obito::datafield::IntegerFieldEnum;
			int* valuePtr = &value;
			memcpy(valuePtr, initStr, sizeof(value));
		}

		IntegerField::IntegerField(int theValue)
		{
			dataFieldEnum = obito::datafield::IntegerFieldEnum;
			value = theValue;
		}

		IntegerField::~IntegerField()
		{
			//
		}

		size_t IntegerField::getValueSize()
		{
			return sizeof(int);
		}

		void IntegerField::printValue()
		{
			std::cout << value;
		}

		std::string IntegerField::getValueByStr()
		{
			return std::to_string(value);
		}

		char* IntegerField::toBinary()
		{
			return reinterpret_cast<char*>(&value);
		}

} }