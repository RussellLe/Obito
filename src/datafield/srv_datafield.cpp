#include "srv_datafield.h"



namespace obito {
	namespace datafield {

		size_t getValueSizeByDFE(DataFieldEnum dfe)
		{
			switch (dfe)
			{
			case obito::datafield::DataFieldEnum::StringFieldEnum:
				return STRING_FIELD_LENGTH;
			case obito::datafield::DataFieldEnum::IntegerFieldEnum:
				return sizeof(int);
			case obito::datafield::DataFieldEnum::DoubleFieldEnum:
				return sizeof(double);
			case obito::datafield::DataFieldEnum::FloatFieldEnum:
				return sizeof(float);
			default:
				return 0;
			}
		}

	}
}