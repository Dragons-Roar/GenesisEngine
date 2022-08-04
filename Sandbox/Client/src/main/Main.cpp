#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <GenesisCore/event/Event.hpp>
#include <GenesisClientCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::clientcore::WindowProps props("Genesis Engine Sandbox", 1920, 1080);
	ge::clientcore::IWindow* window = ge::clientcore::IWindow::create(props);

	std::cout << window->toString() << std::endl;

	while(!window->shouldClose()) {
		window->onUpdate();
	}
}
