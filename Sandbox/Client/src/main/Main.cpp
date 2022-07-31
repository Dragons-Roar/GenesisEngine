#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::ConfigFile file("./config.toml");
	file.load();

	ge::core::ConfigSection section = file.getSection("Server");

	std::cout << section.getDefaultString("name", "Genesis Server") << std::endl;
	std::cout << section.getDefaultString("motd", "A Server using Genesis Engine") << std::endl;
	std::cout << section.getDefaultUInt32("port", 20176) << std::endl;
	std::cout << section.getDefaultIntList<uint32>("test", ge::core::List<uint32>({ 77, 88, 92, 32, 54, 45 })).join(",") << std::endl;;

	file.save();
}
