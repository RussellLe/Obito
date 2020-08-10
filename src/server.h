#pragma once
#include "stdafx.h"
#include "transaction/transaction_mgr.h"
#include "transaction/transaction_obj.h"
#include "api.h"


namespace obito {
	namespace server {

		class ObitoServer
		{
		public:
			ObitoServer(int port, const obito::global::GlobalModuleManager& globalModuleManager);
			~ObitoServer();
			void startCommandHandlers();

		protected:
			WORD sockVersion;
			WSADATA wsaData;
			SOCKET slisten;
			sockaddr_in sin;

		protected:
			obito::api::ObitoApi theApi;
			
			std::map<SOCKET, int> clientTrxIdMap;

		};


	}
}