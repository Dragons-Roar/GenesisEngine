#include <GenesisClient/GenesisClient.hpp>
#include <GenesisServer/GenesisServer.hpp>
#include <GenesisCore/GenesisCore.hpp>
#include <iostream>

namespace ge {
	namespace client {
		void GenesisClient::init() {
			std::cout << "Inititalizing Genesis Client..." << std::endl;
			server::GenesisServer::init();
		}
	}
}
