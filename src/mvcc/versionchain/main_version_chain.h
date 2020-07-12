#pragma once
#include "i_version_chain.h"



namespace obito {
	namespace versionchain {

		class MainVersionChain : public IVersionChain
		{
		public:
			MainVersionChain();
			~MainVersionChain();
			Row readRow(int id, int transactionId);
			Row readPreRow(int id, int transactionId);
			Row readLatestRow(int id);
			bool addRow(Row row);
			bool deleteRow(int id, int transactionId);

		protected:
			std::map<int, std::shared_ptr<std::list<std::pair<int,Row>>>> versionChainMap_;		//transactionId:id:row
		};

	}
}