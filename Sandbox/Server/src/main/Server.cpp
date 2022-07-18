#include <iostream>
#include <SandboxServer/Server.hpp>
#include <GenesisServer/GenesisServer.hpp>

namespace sb {
	namespace server {
		void Server::launch() {
			std::cout << "Starting Sandbox Server..." << std::endl;
			ge::server::GenesisServer::init();
		}
	}
}
