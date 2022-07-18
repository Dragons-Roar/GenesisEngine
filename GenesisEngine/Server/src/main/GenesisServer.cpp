#include <GenesisServer/GenesisServer.hpp>
#include <GenesisCore/GenesisCore.hpp>
#include <iostream>

namespace ge {
	namespace server {
		void GenesisServer::init() {
			std::cout << "Inititalizing Genesis Server..." << std::endl;
			core::GenesisCore::init();
		}
	}
}
