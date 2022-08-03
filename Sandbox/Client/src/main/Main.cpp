#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <GenesisCore/event/Event.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::Event* e = new ge::core::MouseButtonDownEvent(0);
	std::cout << e->toString() << std::endl;
}
