#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

namespace obito {
	namespace client {

		class ClientContext
		{
		public:
			ClientContext(std::string host, int port);
			~ClientContext();
			void sendCommand(std::string command);

		public:
			int transactionId;

		protected:
			WORD sockVersion;
			WSADATA data;

			SOCKET sclient;
			sockaddr_in serAddr;
		};

	}
}