#pragma once
#include "GenesisClientCore/Application.hpp"
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/command/Command.hpp"

namespace ge {
	namespace clientcore {
		class CommandStop: public ge::core::Command {
		public:
			virtual bool onExecute(const std::vector<String>& args) {
				GE_Info("Stopping...");
				Application::getInstance().stop();
				return true;
			}
			virtual String getName() const {
				return "stop";
			}
			virtual bool canRunCommand() const {
				return true;
			}
		};
	}
}
