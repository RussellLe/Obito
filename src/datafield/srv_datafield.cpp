#include "srv_datafield.h"



namespace obito {
	namespace datafield {

		size_t getValueSizeByDFE(DataFieldEnum dfe)
		{
			switch (dfe)
			{
			case 2:
				return sizeof(int);
			default:
				return 0;
			}
		}

	}
}