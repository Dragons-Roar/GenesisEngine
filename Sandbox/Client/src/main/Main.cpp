#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::ConfigFile file("./config.toml");
	file.load();

	std::cout << "Port: " << file.getUInt32("Server.port", true) << std::endl;

	std::cout << file.keys(true).join(",") << std::endl;

	std::cout << "Name: " << file.getString("Server.name") << std::endl;
	std::cout << "Port: " << file.getString("Server.port") << std::endl;

	file.getSection("Server").keys(true, [](const String& key) {
		std::cout << "Key: " << key << std::endl;
	});

	file.save();
}
