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
        std::string generateTableFileName(std::string tableName);

        std::string generateDataFileName(std::string tableName);

        std::vector<std::string> splitStr(std::string originStr, char token);
    }
}