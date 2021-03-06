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
#include "mvcc/versionchain/main_version_chain.h"
#include "transaction/transaction_mgr.h"
#include "transaction/transaction_obj.h"
#include "api.h"
#include "server.h"

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
		row.transactionId = 999;
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

void versionChainTest()
{
	obito::versionchain::MainVersionChain mvc;
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>("testbuffertable");
	for (int i = 1; i < 10; i++)
	{
		obito::table::Value v1(std::make_shared<obito::datafield::FloatField>(6.6));
		obito::table::Value v2(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
		obito::table::Value v3(std::make_shared<obito::datafield::DoubleField>(33.33 + i));
		std::vector<obito::table::Value> values;
		values.push_back(v1);
		values.push_back(v2);
		values.push_back(v3);
		Row row(tablePtr, 1, values);
		row.setTransactionId(i);
		mvc.addRow(row);
		if (i == 9)
		{
			Row updaterow(tablePtr, 1, values);
			updaterow.setTransactionId(2);
			mvc.addRow(updaterow);
		}
	}
	mvc.deleteRow(1, 8);
	for (int i = 1; i < 10; i++)
	{
		Row row = mvc.readRow(1, i);
		row.printRow();
	}
}

void transactionTest()
{
	std::string tableName = "testtransactiontable";

	obito::table::Column c1("oneColumn", obito::datafield::FloatFieldEnum);
	obito::table::Column c2("twoColumn", obito::datafield::StringFieldEnum);
	obito::table::Column c3("threeColumn", obito::datafield::DoubleFieldEnum);
	std::vector<obito::table::Column> columns;
	columns.push_back(c1);
	columns.push_back(c2);
	columns.push_back(c3);
	std::shared_ptr<obito::table::Table> tablePtr = std::make_shared<obito::table::Table>(tableName);
	std::shared_ptr<obito::presistence::PresistenceHandler> phptr=std::make_shared<obito::presistence::PresistenceHandler>(tablePtr, columns);

	obito::global::GlobalModuleManager gmm;
	gmm.tablePresistenceMap.addTablePresistencePair(tableName, phptr);
	obito::transaction::TransactionManager trxmgr(gmm);
	int trx1 = trxmgr.begin();
	cout << trxmgr.checkTransactionExist(trx1) << endl;

	obito::table::Value v1(std::make_shared<obito::datafield::FloatField>(6.6));
	obito::table::Value v2(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
	obito::table::Value v3(std::make_shared<obito::datafield::DoubleField>(33.33));
	std::vector<obito::table::Value> values;
	values.push_back(v1);
	values.push_back(v2);
	values.push_back(v3);
	Row row(tablePtr, 1, values);
	trxmgr.addRow(trx1, tableName,row);
	trxmgr.readRow(trx1, tableName, 1);
	trxmgr.commit(trx1);


	obito::table::Value v4(std::make_shared<obito::datafield::FloatField>(7.7));
	obito::table::Value v5(std::make_shared<obito::datafield::StringField>("HELLOWORLD"));
	obito::table::Value v6(std::make_shared<obito::datafield::DoubleField>(22.33));
	std::vector<obito::table::Value> values2;
	values2.push_back(v4);
	values2.push_back(v5);
	values2.push_back(v6);
	Row row2(tablePtr, 1, values2);
	int trx2 = trxmgr.begin();
	trxmgr.readRow(trx2, tableName, 1).printRow();
	trxmgr.updateRow(trx2, tableName, row2);
	trxmgr.readRow(trx2, tableName, 1).printRow();
	trxmgr.rollback(trx2);
	int trx3 = trxmgr.begin();
	trxmgr.readRow(trx3, tableName, 1).printRow();
}

void testByCmdApi()
{
	obito::global::GlobalModuleManager gmm;
	obito::api::ObitoApi theApi(gmm);
	
	std::string command;
	while (cin >> command)
	{
		theApi.exeObitoCmd(command, 1);
	}
}

int socketServerScript()
{
	WORD sockVersion = MAKEWORD(2, 2);//指定socket版本2.2
	WSADATA wsaData;//存储被WSAStartup函数调用后返回的Windows Sockets数据
	if (WSAStartup(sockVersion, &wsaData) != 0) return 0;

	//创建服务端socket,三个参数分别代表IP地址族，流式套接字，TCP协议
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error!");
		return 0;
	}

	//绑定服务端ip和端口
	sockaddr_in sin;//存放了地址族、端口、ip地址，用来处理通信地址
	sin.sin_family = AF_INET;//ip地址族
	sin.sin_port = htons(8888);//转换网络编码,侦听本地8888端口
	sin.sin_addr.S_un.S_addr = INADDR_ANY;//接收任意地址的连接
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error!");
	}

	//开始侦听
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error!");
		return 0;
	}

	SOCKET sClient;//创建客户端socket
	sockaddr_in remoteAddr;//客户端的地址信息
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];//接收数据缓冲区

	//循环接收数据
	while (1)
	{
		printf("waiting...\n");
		//等待连接，返回客户端socket
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error!");
			continue;
		}
		printf("Connection successful:%s\n", inet_ntoa(remoteAddr.sin_addr));

		//接收数据
		int ret = recv(sClient, revData, 255, 0);//若无错误，返回读入字节数
		if (ret > 0)
		{
			revData[ret] = '\0';
			printf("%s\n", revData);
		}

		//发送数据
		char sendData[255];
		gets_s(sendData);
		send(sClient, sendData, strlen(sendData), 0);

		closesocket(sClient);
	}

	closesocket(slisten);//关闭服务端socket
	WSACleanup();
}

void startServer()
{
	obito::global::GlobalModuleManager gmm;
	obito::server::ObitoServer server(8888, gmm);
	server.startCommandHandlers();
}

int main()
{
	obito::server::ObitoServer server(8888, *(new obito::global::GlobalModuleManager));
	server.startCommandHandlers();
	return 0;
}