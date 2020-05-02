#include <iostream>
#include "stdafx.h"
#include "util.h"
#include "table.h"


using namespace std;

int main()
{
	obito::table::Column c1("testcolumn",3,4);
	std::string tmp = c1.toString();
	cout << tmp << endl;
	obito::table::Column c2(tmp);
	cout << c2.columnName << endl;
	cout << c2.valueType << endl;
	cout << c2.size << endl;
	return 0;
}