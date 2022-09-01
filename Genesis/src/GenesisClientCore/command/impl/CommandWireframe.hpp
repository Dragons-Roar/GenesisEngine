#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include <GenesisCore/command/Command.hpp>

namespace ge {
	namespace clientcore {
		class CommandWireframe: public ge::core::Command {
		public:
			bool onExecute(const std::vector<String>& args) {
				if(args.size() < 1) return false;
				String arg = args[0];
				if(arg == "enable" || arg == "true") {
					RenderCommand::setWireframeMode(true);
				} else if(arg == "disable" || arg == "false") {
					RenderCommand::setWireframeMode(false);
				}
				return true;
			}
			String getName() const {
				return "wireframe";
			}
			bool canRunCommand() const {
				return true;
			}
		};
	}
}
