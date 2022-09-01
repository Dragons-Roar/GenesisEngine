#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/GenesisBase.hpp"
#include "GenesisCore/command/Command.hpp"

namespace ge {
	namespace core {
		namespace exceptions {
			struct CommandNotFound: public ge::core::exceptions::GenesisRuntimeException {
				CommandNotFound(const String& name, const String& in): GenesisRuntimeException("Command '" + name + "' could not be found!") {}
			};
			struct CommandError: public ge::core::exceptions::GenesisRuntimeException {
				CommandError(const String& name, const String& in): GenesisRuntimeException("Command '" + name + "' did not run successfully!") {}
			};
		}

		class CommandManager {
		public:
			using CommandList = std::vector<Ref<Command>>;
			using CommandMap = std::unordered_map<String, Ref<Command>>;

			static void init();
			static void shutdown();

			static void addCommand(const Ref<Command> command);
			static void runCommand(String command);
			static bool exists(const String& name);

			static const CommandList& getCommands();

		private:
			static void _runCommand(const String& command);

			static CommandMap commands;
		};
	}
}
