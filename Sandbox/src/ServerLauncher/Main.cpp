#include <iostream>
#include <Server/Server.hpp>

int main(int argc, char** argv) {
	std::cout << "Starting Server..." << std::endl;

	sb::server::Server server;
	server.launch();
}
