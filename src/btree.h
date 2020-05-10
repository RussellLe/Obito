#pragma once

#include "stdafx.h"
#include "util.h"
#include "table.h"


namespace obito {
	namespace index {

		typedef obito::table::ValueRow ValueRow;

		class BTreeNode
		{
		public:
			int id;
			ValueRow valueRow;
			BTreeNode(ValueRow theValueRow);
		};

		class BTree
		{
		public:
			bool addNode(BTreeNode theNode);
		protected:
			size_t nodeSize_;
		};

	}
}