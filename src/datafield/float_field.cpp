#include "float_field.h"

namespace obito {
	namespace datafield {


		FloatField::FloatField()
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::FloatFieldEnum;
		}

		FloatField::FloatField(char* initStr)
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::FloatFieldEnum;
			memcpy(&value, initStr, sizeof(value));
		}

		FloatField::FloatField(float theValue)
		{
			dataFieldEnum = obito::datafield::DataFieldEnum::FloatFieldEnum;
			value = theValue;
		}

		FloatField::~FloatField()
		{
			//
		}

		size_t FloatField::getValueSize()
		{
			return sizeof(float);
		}

		void FloatField::printValue()
		{
			std::cout << value;
		}

		char* FloatField::toBinary()
		{
			return reinterpret_cast<char*>(&value);
		}

		std::string FloatField::getValueByStr()
		{
			return std::to_string(value);
		}

	}
}