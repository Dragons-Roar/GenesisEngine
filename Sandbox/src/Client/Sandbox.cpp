#include <GenesisClientCore/Genesis.hpp>
#include <GenesisClientCore/ClientEntryPoint.hpp>
#include <iostream>

#include "SandboxLayer.hpp"
#include "Sandbox2D.hpp"
#include "Sandbox3D.hpp"

class Sandbox: public ge::clientcore::Application {
public:
	Sandbox(const ge::clientcore::ApplicationConfiguration& config): ge::clientcore::Application(config) {
		//pushLayer(new sb::SandboxLayer());
		//pushLayer(new sb::Sandbox2D());
		pushLayer(new sb::Sandbox3D());
	}
	~Sandbox() {}
};

ge::clientcore::Application* ge::clientcore::createApplication() {
	ApplicationConfiguration config;
	config.name = "Genesis Sandbox";
	config.width = 1920;
	config.height = 1080;

	return new Sandbox(config);
}
