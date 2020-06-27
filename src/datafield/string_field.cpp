#include "string_field.h"



namespace obito {
	namespace datafield {

		StringField::StringField()
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::StringFieldEnum;
		}

		StringField::StringField(char* initStr)
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::StringFieldEnum;
			value = initStr;
		}

		StringField::StringField(std::string theValue)
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::StringFieldEnum;
			value = theValue;
		}

		StringField::~StringField()
		{
			//
		}

		char* StringField::toBinary()
		{
			return const_cast<char*>(value.data());
		}

		size_t StringField::getValueSize()
		{
			return STRING_FIELD_LENGTH;
		}

		void StringField::printValue()
		{
			std::cout << value;
		}

	}
}