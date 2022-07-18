#include <iostream>
#include <SandboxServer/Server.hpp>

int main(int argc, char** argv) {
	std::cout << "Starting Server..." << std::endl;

	sb::server::Server server;
	server.launch();
}
