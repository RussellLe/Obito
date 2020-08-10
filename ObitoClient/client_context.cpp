#include "client_context.h"
#include <string>

namespace obito {
	namespace client {

		ClientContext::ClientContext(std::string host, int port)
		{
			sockVersion = MAKEWORD(2, 2);
			WSAStartup(sockVersion, &data);
			sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			serAddr.sin_family = AF_INET;
			serAddr.sin_port = htons(port);
			serAddr.sin_addr.S_un.S_addr = inet_addr(host.c_str());

			connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr));
		}

		ClientContext::~ClientContext()
		{
			closesocket(sclient);
			WSACleanup();
		}

		void ClientContext::sendCommand(std::string command)
		{
			send(sclient, command.c_str(), strlen(command.c_str()), 0);

			char recData[255];
			int ret = recv(sclient, recData, 255, 0);
			if (ret > 0) {
				recData[ret] = '\0';
				printf(recData);
			}
			printf("\n");
		}

	}
}