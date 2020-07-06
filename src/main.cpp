#include <iostream>
#include "stdafx.h"
#include "util.h"
#include "table.h"
#include "index/memory_rbtree.h"
#include "datafield/integer_field.h"
#include "datafield/string_field.h"
#include "datafield/double_field.h"
#include "datafield/float_field.h"
#include <bitset>
#include "presistence.h"
#include "cache/i_cache.h"
#include "cache/main_cache.h"

using namespace std;

void script1()
{
	obito::table::Column c1("oneColumn", obito::datafield::IntegerFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::IntegerFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::IntegerFieldEnum);
	auto t1 = new obito::table::Table("TestTable");
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
	cout << tablePtr->getValueRowSize() << endl;
	cout << r1.getValueRowSize() << endl;
	cout << r2.getValueRowSize() << endl;
}

void writeRowScript()
{
	obito::table::Column c1("oneColumn", obito::datafield::FloatFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::StringFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::DoubleFieldEnum);
	std::vector<obito::table::Column> columns;
	columns.push_back(c1);
	columns.push_back(c2);
	columns.push_back(c3);
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>("presistencetable");
	obito::presistence::PresistenceHandler ph(tablePtr, columns);
	obito::table::Value v1(std::make_shared<obito::datafield::FloatField>(6.6));
	obito::table::Value v2(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
	obito::table::Value v3(std::make_shared<obito::datafield::DoubleField>(33.33));
	std::vector<obito::table::Value> values;
	values.push_back(v1);
	values.push_back(v2);
	values.push_back(v3);
	std::vector<Row> rows;
	for (int i = 1; i < 500; i++)
	{
		Row row(tablePtr, i, values);
		rows.push_back(row);
	}
	ph.writeRows(rows);
}

void readRowScript()
{
	obito::table::Column c1("oneColumn", obito::datafield::FloatFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::StringFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::DoubleFieldEnum);
	std::vector<obito::table::Column> columns;
	columns.push_back(c1);
	columns.push_back(c2);
	columns.push_back(c3);
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>("presistencetable");
	obito::presistence::PresistenceHandler ph(tablePtr, columns);
	for (int i = 1; i < 500; i++)
	{
		Row row = ph.readRow(i);
		row.printRow();
	}
}

void testCacheScript()
{
	obito::cache::MainCache mbp;
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>("testbuffertable");
	obito::table::Value v1(std::make_shared<obito::datafield::FloatField>(6.6));
	obito::table::Value v2(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
	obito::table::Value v3(std::make_shared<obito::datafield::DoubleField>(33.33));
	std::vector<obito::table::Value> values;
	values.push_back(v1);
	values.push_back(v2);
	values.push_back(v3);
	for (int i = 1; i < 300; i++)
	{
		obito::table::Row r_tmp(tablePtr, i, values);
		mbp.addToCache(r_tmp);
	}
	std::cout << mbp.checkIdExist(3) << std::endl;
	cout << mbp.checkIdExist(30) << endl;
	cout << mbp.checkIdExist(128) << endl;
	mbp.readFromCache(128).printRow();
	mbp.readFromCache(149).printRow();
	mbp.readFromCache(29).printRow();
	mbp.readFromCache(132).printRow();
	for (auto iter = mbp.idLink.begin(); iter != mbp.idLink.end(); iter++)
	{
		std::cout << *iter << ' ';
	}
	cout << endl;
	std::cout << "middle in:" << *mbp.idLinkMiddle << endl;
}


void commandTestScript()
{
	std::string command;
	int num;
	obito::table::Column c1("oneColumn", obito::datafield::FloatFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::StringFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::DoubleFieldEnum);
	std::vector<obito::table::Column> columns;
	columns.push_back(c1);
	columns.push_back(c2);
	columns.push_back(c3);
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>("presistencetable");
	obito::presistence::PresistenceHandler ph(tablePtr, columns);
	obito::table::Value v1(std::make_shared<obito::datafield::FloatField>(6.6));
	obito::table::Value v2(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
	obito::table::Value v3(std::make_shared<obito::datafield::DoubleField>(33.33));
	std::vector<obito::table::Value> values;
	values.push_back(v1);
	values.push_back(v2);
	values.push_back(v3);
	int id = 1;
	while (cin >> command >> num)
	{
		if (command == "add")
		{
			for (int i = 0; i < num; i++)
			{
				std::cout << "writing id:" << id << endl;
				Row row(tablePtr, id, values);
				row.transactionId = 999;
				ph.addRow(row);
				id++;
			}
		}
		else if (command == "query")
		{
			Row row = ph.readRow(num);
			row.printRow();
		}
		else if (command == "exit")
		{
			return;
		}
		else
		{
			std::cout << "error command" << std::endl;
		}
	}
}


int main()
{
	commandTestScript();
	return 0;
}