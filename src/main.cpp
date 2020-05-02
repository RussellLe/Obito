#include <iostream>
#include "stdafx.h"
#include "util.h"
#include "table.h"


using namespace std;

int main()
{
	obito::table::Value v1("lubenweiniubi",3);
	std::string tmp = v1.toString();
	std::string output=obito::file::readStringFromFile("test.dat", tmp.size(),20 );
	return 0;
}