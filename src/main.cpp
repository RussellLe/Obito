#include <iostream>
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/memory_rbtree.h"
#include "datafield/integer_field.h"
#include <bitset>


using namespace std;

int main()
{
	obito::table::Column c1("oneColumn", obito::datafield::IntegerFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::IntegerFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::IntegerFieldEnum);
	auto t1=new obito::table::Table("TestTable");
	t1->addColumn(c1);
	t1->addColumn(c2);
	t1->addColumn(c3);
	std::shared_ptr<obito::table::Table> tablePtr(t1);
	cout << "complete column add" << endl;

	obito::table::Value v1(std::make_shared<obito::datafield::IntegerField>(3));
	obito::table::Value v2(std::make_shared<obito::datafield::IntegerField>(5));
	obito::table::Value v3(std::make_shared<obito::datafield::IntegerField>(99));

	std::vector<obito::table::Value> values;
	values.push_back(v1);
	values.push_back(v2);
	values.push_back(v3);
	cout << "complete value init" << endl;
	obito::table::Row r1(tablePtr, 1, values);
	char* initStr = r1.toBinary();
	cout << initStr << endl;
	obito::table::Row r2(tablePtr, initStr);
	cout << r2.id << endl;
	r2.printRow();
	return 0;
}