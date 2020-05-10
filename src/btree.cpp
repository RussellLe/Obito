#include "btree.h"

namespace obito {
	namespace index {

		BTreeNode::BTreeNode(ValueRow theValueRow)
			: valueRow(theValueRow)
		{
			id = theValueRow.id;
		}

} }