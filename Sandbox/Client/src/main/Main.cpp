#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::ConfigFile file("./config.toml");
	file.load();

	std::cout << file.getSection("Server").getSection("test2").getSection("lol").getDefaultUInt32("port", 37) << std::endl;
	std::cout << file.getSection("Server").getSection("test2").getDefaultBool("enable", false) << std::endl;
	std::cout << "Port: " << file.getUInt32("Server.port", true) << std::endl;

	std::cout << file.getSection("Server").keys(true).join(",") << std::endl;

	std::cout << "Name: " << file.getString("Server.name", true) << std::endl;

	file.getSection("Server").keys(true, [](const String& key) {
		std::cout << "Key: " << key << std::endl;
	});

	file.save();
}
