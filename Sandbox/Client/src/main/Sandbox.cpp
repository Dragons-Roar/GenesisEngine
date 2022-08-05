#include <GenesisCore/Genesis.hpp>
#include <GenesisCore/event/Event.hpp>
#include <GenesisClientCore/Genesis.hpp>
#include <GenesisClientCore/ClientEntryPoint.hpp>
#include <iostream>

class Sandbox: public ge::clientcore::Application {
public:
	Sandbox(const ge::clientcore::ApplicationConfiguration& config): ge::clientcore::Application(config) {}
	~Sandbox() {}
};

ge::clientcore::Application* ge::clientcore::createApplication() {
	ApplicationConfiguration config;
	config.name = "Genesis Sandbox";

	return new Sandbox(config);
}
