#include <GenesisClientCore/Genesis.hpp>
#include <GenesisClientCore/ClientEntryPoint.hpp>
#include <iostream>

#include "SandboxLayer.hpp"

class Sandbox: public ge::clientcore::Application {
public:
	Sandbox(const ge::clientcore::ApplicationConfiguration& config): ge::clientcore::Application(config) {
		pushLayer(new sb::SandboxLayer());
	}
	~Sandbox() {}
};

ge::clientcore::Application* ge::clientcore::createApplication() {
	ApplicationConfiguration config;
	config.name = "Genesis Sandbox";

	return new Sandbox(config);
}
