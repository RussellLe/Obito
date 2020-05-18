#pragma once
#include "../stdafx.h"
#include "../util.h"
#include "../table.h"


typedef obito::table::Row Row;

namespace obito {
	namespace presistence {

		class PresistenceHandler
		{
		public:
			std::string fileName;

		public:
			PresistenceHandler(std::string theFileName);
			bool writeRow(Row row);
		};

} }