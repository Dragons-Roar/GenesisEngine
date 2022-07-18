#include <GenesisClient/GenesisClient.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();
}
