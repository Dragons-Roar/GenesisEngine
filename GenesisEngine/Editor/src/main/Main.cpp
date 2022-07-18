#include <GenesisCore/GenesisCore.hpp>
#include <GenesisClient/GenesisClient.hpp>
#include <GenesisServer/GenesisServer.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Genesis Editor..." << std::endl;
	ge::core::GenesisCore::init();
}
