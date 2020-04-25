#pragma once

#include "stdafx.h"

namespace obito {
    namespace file {

        bool createFile(std::string fileName);

        bool writeToFile(std::string fileName, const char* value, int valueSize, int offset);

        bool readFromFile(std::string fileName, char* readBuffer, int valueSize, int offset);
    }
}