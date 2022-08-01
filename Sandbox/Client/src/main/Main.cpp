#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::UUID uuid;
	std::cout << uuid.toString() << std::endl;
	std::cout << uuid.format() << std::endl;
	std::cout << uuid.formatTrimmed() << std::endl;

	uuid = ge::core::UUID::nil;
	std::cout << uuid.toString() << std::endl;
	std::cout << uuid.format() << std::endl;
	std::cout << uuid.formatTrimmed() << std::endl;
}
