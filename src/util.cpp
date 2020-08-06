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

        bool deleteFile(std::string fileName)
        {
            bool flag = remove(fileName.c_str());
            if (flag)
            {
                return false;
            }
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

        bool writeStringToFile(std::string fileName, std::string writeStr, int offset)
        {
            return writeToFile(fileName, writeStr.c_str(), writeStr.size(), offset);
        }

        std::string readStringFromFile(std::string fileName, int valueSize, int offset)
        {
            char* buffer = (char*)malloc(valueSize * sizeof(char));
            readFromFile(fileName, buffer, valueSize, offset);
            std::string output = buffer;
            return output;
        }

        char* readAllBinaryFromFile(std::string fileName)
        {
            std::ifstream in(fileName);
            std::ostringstream tmp;
            tmp << in.rdbuf();
            std::string str = tmp.str();

            char* output = (char*)malloc(str.length());
            for (int i = 0; i < str.length(); i++)
            {
                output[i] = str[i];
            }

            return output;
        }

        std::string readAllStringFromFile(std::string fileName)
        {
            std::ifstream in(fileName, std::ios::binary);
            std::ostringstream tmp;
            tmp << in.rdbuf();
            std::string str = tmp.str();
            return str;
        }

        char* turnStdStringToBinary(std::string originStr)
        {
            char* output = (char*)malloc(originStr.length());
            for (int i = 0; i < originStr.length(); i++)
            {
                output[i] = originStr[i];
            }
            return output;
        }

        bool isFileExist(std::string fileName)
        {
            std::ifstream f(fileName.c_str());
            return f.good();
        }
    }
}

namespace obito
{
    namespace common
    {
        std::string generateTableInfoFileName(std::string tableName)
        {
            return tableName + "TableInfo.dat";
        }

        std::string generateTableDataFileName(std::string tableName)
        {
            return tableName + "Data.dat";
        }

        std::string generateColumnsFileName(std::string tableName)
        {
            return tableName + "Columns.dat";
        }

        std::string generateIndexFileName(std::string indexName)
        {
            return indexName + "Index.dat";
        }

        std::string generateIndexFragsFileName(std::string indexName)
        {
            return indexName + "IndexFrags.dat";
        }

        int turnStrToInteger(std::string theStr)
        {
            return std::stoi(theStr);
        }

        double turnStrToDouble(std::string theStr)
        {
            return std::stod(theStr);
        }
        
        float turnStrToFloat(std::string theStr)
        {
            return std::stof(theStr);
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