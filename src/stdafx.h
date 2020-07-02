#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <map>
#include <list>

#define _CRT_SECURE_NO_WARNINGS
#pragma  warning (disable:4996) 

#define VALUE_SPLIT_CONST_CHAR_PTR "|"
#define VALUE_SPLIT_CHAR '|'

#define STRING_FIELD_LENGTH 255

#define MAIN_BUFFER_POOL_SIZE 255

#define MAIN_CACHE_MAX_SIZE 255
static const double MAIN_CACHE_HOT_RATE = 0.33;

typedef unsigned int _value_type_int;