#include "util.h"

namespace obito {
    namespace file {

        bool createFile(std::string fileName)
        {
            std::ofstream outFile;
            outFile.open(fileName);
            outFile.close();
            return true;
        }

        bool writeToFile(std::string fileName, const char* value, int valueSize, int offset)
        {
            std::ofstream outFile(fileName, std::ios::out | std::ios::binary | std::ios::in);
            outFile.seekp(offset, std::ios::beg);
            outFile.write(value, valueSize);
            outFile.close();
            return true;
        }

        bool readFromFile(std::string fileName, char* readBuffer, int valueSize, int offset)
        {
            std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
            inFile.seekg(offset, std::ios::beg);
            inFile.read(readBuffer, valueSize);
            inFile.close();
            return true;
        }
    }
}

namespace obito
{
    namespace common
    {
        std::string generateTableFileName(std::string tableName)
        {
            return tableName + "TableInfo.dat";
        }

        std::string generateDataFileName(std::string tableName)
        {
            return tableName + "Data.dat";
        }

        std::vector<std::string> splitStr(std::string originStr, char token)
        {
            std::vector<std::string> output;
            std::string tmp="";
            for (int i = 0; i < originStr.size(); i++)
            {
                if (originStr[i] == token)
                {
                    output.push_back(tmp);
                    tmp = "";
                    continue;
                }
                tmp += originStr[i];
            }
            output.push_back(tmp);
            return output;
        }
    }
}