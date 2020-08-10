#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <map>
#include <list>
#include <iterator>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  

#define _CRT_SECURE_NO_WARNINGS
#pragma  warning (disable:4996) 

#define WORD_SPLIT_SYMBOL ' '
#define VALUE_SPLIT_SYMBOL ','

#define STRING_FIELD_LENGTH 255

#define MAIN_BUFFER_POOL_SIZE 255

#define MAIN_CACHE_MAX_SIZE 255
static const double MAIN_CACHE_HOT_RATE = 0.33;

typedef unsigned int _value_type_int;

#define ERROR_ROW_FLAG -1
#define NONE_TRANSACTION_ID 0

#define CREATE_TABLE_KEYWORD "createtable"
#define ADD_KEYWORD "add"
#define READ_KEYWORD "read"
#define UPDATE_KEYWORD "update"
#define DELETE_KEYWORD "delete"
#define BEGIN_KEYWORD "begin"
#define COMMIT_KEYWORD "commit"
#define ROLLBACK_KEYWORD "rollback"

#define INTEGER_FIELD_KEYWORD "integer"
#define DOUBLE_FIELD_KEYWORD "double"
#define STRING_FIELD_KEYWORD "string"
#define FLOAT_FIELD_KEYWORD "float"