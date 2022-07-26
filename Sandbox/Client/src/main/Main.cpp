#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/List.hpp>
#include <GenesisCore/Version.hpp>
#include <GenesisCore/String.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();
}
