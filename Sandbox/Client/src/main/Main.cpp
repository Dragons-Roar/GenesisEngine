#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::ConfigFile file("./config.toml");
	file.load();
	ge::core::ConfigSection section = file.getSection("Server");
	section.setFloat32("test", 739.333f);

	std::cout << section.getString("name") << std::endl;
	std::cout << section.getFloat32("slots") << std::endl;
	std::cout << file.getString("test") << std::endl;

	file.save();
}
