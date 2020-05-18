#pragma once

#include "stdafx.h"

namespace obito {
    namespace file {

        bool createFile(std::string fileName);

        bool deleteFile(std::string fileName);

        bool writeToFile(std::string fileName, const char* value, int valueSize, int offset);

        bool readFromFile(std::string fileName, char* readBuffer, int valueSize, int offset);

        bool writeStringToFile(std::string fileName, std::string writeStr, int offset);

        std::string readStringFromFile(std::string fileName, int valueSize, int offset);

        std::string readAllStringFromFile(std::string fileName);

        char* readAllBinaryFromFile(std::string fileName);

        char* turnStdStringToBinary(std::string originStr);

        bool isFileExist(std::string fileName);

        template <typename T> T* readObjectFromFile(std::string fileName, int offset)
        {
            char* buffer = (char*)malloc(sizeof(T));
            obito::file::readFromFile(fileName, buffer, sizeof(T), offset);

            T* outputPtr = new T;
            memcpy(outputPtr, buffer, sizeof(T));
            return outputPtr;
        }
    }
}

namespace obito
{
    namespace common
    {
        std::string generateTableInfoFileName(std::string tableName);

        std::string generateTableDataFileName(std::string tableName);

        std::string generateColumnsFileName(std::string tableName);

        std::string generateIndexFileName(std::string indexName);

        std::string generateIndexFragsFileName(std::string indexName);

        std::vector<std::string> splitStr(std::string originStr, char token);

        template <typename T> T* initObjectByStr(char* initStr)
        {
            T* outputPtr = new T();
            memcpy(outputPtr, initStr, sizeof(T));
            return outputPtr;
        }
    }
}