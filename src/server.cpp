#include "server.h"

namespace obito {
	namespace server {

		ObitoServer::ObitoServer(int port, const obito::global::GlobalModuleManager& globalModuleManager)
			: theApi(globalModuleManager)
		{
			sockVersion = MAKEWORD(2, 2);
			WSAStartup(sockVersion, &wsaData);
			slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			sin.sin_family = AF_INET;
			sin.sin_port = htons(port);
			sin.sin_addr.S_un.S_addr = INADDR_ANY;
			bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR;

			listen(slisten, 5);
		}

		ObitoServer::~ObitoServer()
		{
			closesocket(slisten);
			WSACleanup();
		}

		void ObitoServer::startCommandHandlers()
		{
			SOCKET sClient;//创建客户端socket
			sockaddr_in remoteAddr;//客户端的地址信息
			int nAddrlen = sizeof(remoteAddr);

			sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
			if (sClient == INVALID_SOCKET)
			{
				printf("accept error!");
				return;
			}
			printf("Connection successful:%s\n", inet_ntoa(remoteAddr.sin_addr));

			while (1)
			{
				char revData[255];//接收数据缓冲区
				int ret = recv(sClient, revData, 255, 0);//若无错误，返回读入字节数
				if (ret > 0)
				{
					revData[ret] = '\0';
					printf("%s\n", revData);
				}

				std::string command = revData;
				std::string output = "Success";

				if (command == "killserver")
				{
					break;
				}

				std::string keyword = obito::common::splitStr(command, VALUE_SPLIT_SYMBOL)[0];
				if (keyword == BEGIN_KEYWORD)
				{
					clientTrxIdMap.insert(std::pair<SOCKET, int>(
						sClient, std::stoi(theApi.exeObitoCmd(BEGIN_KEYWORD, NONE_TRANSACTION_ID))));
					output = theApi.exeObitoCmd(command,NONE_TRANSACTION_ID);
					send(sClient, output.c_str(), strlen(output.c_str()), 0);
					continue;
				}

				auto cltTrxIter = clientTrxIdMap.find(sClient);
				if (cltTrxIter == clientTrxIdMap.end())
				{
					int trxId=std::stoi(theApi.exeObitoCmd(BEGIN_KEYWORD,NONE_TRANSACTION_ID));
					output = theApi.exeObitoCmd(command, trxId);
					theApi.exeObitoCmd(COMMIT_KEYWORD, trxId);

					send(sClient, output.c_str(), strlen(output.c_str()), 0);
					continue;
				}

				output = theApi.exeObitoCmd(command, cltTrxIter->second);
				if (keyword == COMMIT_KEYWORD || keyword == ROLLBACK_KEYWORD)
				{
					clientTrxIdMap.erase(cltTrxIter);
				}
				send(sClient, output.c_str(), strlen(output.c_str()), 0);
				continue;
			}
			closesocket(sClient);
		}

	}
}