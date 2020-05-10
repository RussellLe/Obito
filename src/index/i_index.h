#pragma once

#include "../stdafx.h"
#include "../util.h"

namespace obito {
	namespace index {

		class IIndex
		{
		public:
			virtual ~IIndex() {};
			virtual int addIndexUnit(int id) = 0;
			virtual int getOffset(int id) = 0;
			virtual bool deleteIndexUnit(int id) = 0;
		};

		class MemoryIndex : public IIndex
		{
		public:
			virtual ~MemoryIndex() {};

		protected:
			std::string indexFileName_;
			std::string indexFragFileName_;
			size_t valueRowSize_;

		protected:
			virtual bool syncIndexToFile() = 0;
			virtual bool loadIndexFromFile() = 0;

		};

		class StorageIndex : public IIndex
		{
		public:
			virtual ~StorageIndex() {};

		protected:
			std::string indexFileName_;
		};

		class IdOffsetUnit
		{
		public:
			int id;
			int offset;
			IdOffsetUnit(){}
			IdOffsetUnit(int theId, int theOffset) { id = theId; offset = theOffset; }
		};

} }