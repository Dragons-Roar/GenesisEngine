#include "GenesisCore/command/CommandManager.hpp"

#include "GenesisCore/Logger.hpp"
#include "GenesisCore/Utils.hpp"

namespace ge {
	namespace core {
		CommandManager::CommandMap CommandManager::commands;

		void CommandManager::init() {
			GE_Info("Initializing Command Manager...");
		}
		void CommandManager::shutdown() {
			GE_Info("Shutting down Command Manager...");
		}

		void CommandManager::addCommand(const Ref<Command> command) {
			commands.insert(std::make_pair(command->getName(), command));
		}
		void CommandManager::runCommand(String command) {
			std::transform(command.begin(), command.end(), command.begin(), ::tolower);

			// TODO: Add command seperator to run multiple commands
			_runCommand(command);
		}
		bool CommandManager::exists(const String& name) {
			return commands.find(name) != commands.end();
		}

		const CommandManager::CommandList& CommandManager::getCommands() {
			CommandList list;
			list.reserve(commands.size());
			for(auto it = commands.begin(); it != commands.end(); ++it) {
				list.push_back(it->second);
			}
			return list;
		}

		void CommandManager::_runCommand(const String& command) {
			String commandName = command.substr(0, command.find_first_of(" "));
			if(!exists(commandName)) {
				GE_ThrowException(exceptions::CommandNotFound(commandName, command));
			}

			std::vector<String> args;
			Utils::splitString(args, command.substr(command.find_first_of(" ") + 1), ' ');
			if(!commands[commandName]->onExecute(args)) {
				GE_ThrowException(exceptions::CommandError(commandName, command));
			}
		}
	}
}
