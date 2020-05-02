#pragma once

#include "stdafx.h"

namespace obito {
    namespace file {

        bool createFile(std::string fileName);

        bool writeToFile(std::string fileName, const char* value, int valueSize, int offset);

        bool readFromFile(std::string fileName, char* readBuffer, int valueSize, int offset);
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