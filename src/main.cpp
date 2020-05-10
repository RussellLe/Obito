#include <iostream>
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/memory_rbtree.h"
#include <bitset>


using namespace std;

int main()
{
	obito::index::MemoryRBTree mrbt("testindex.dat", "testindexfrag.dat", 3);
	return 0;
}