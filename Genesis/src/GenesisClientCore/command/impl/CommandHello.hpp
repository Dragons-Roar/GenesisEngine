#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include <GenesisCore/command/Command.hpp>

namespace ge {
	namespace clientcore {
		class CommandHello: public ge::core::Command {
		public:
			bool onExecute(const std::vector<String>& args) {
				GE_Info("Hello Command World!");
				return true;
			}
			String getName() const {
				return "hello";
			}
			bool canRunCommand() const {
				return true;
			}
		};
	}
}
