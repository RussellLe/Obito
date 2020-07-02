#pragma once


#include "../stdafx.h"
#include "../util.h"
#include "../table.h"


typedef obito::table::Row Row;

namespace obito {
	namespace buffer {
		
		class IBufferPool
		{
		public:
			virtual bool addToBuffer(Row row) = 0;
			virtual void updateFlushFlag() = 0;
			virtual bool checkIdExist(int id) = 0;
			virtual Row readFromBuffer(int id) = 0;

		};



	}
}