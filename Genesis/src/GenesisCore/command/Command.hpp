#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		class Command {
		public:
			/**
			 * @brief Will be called if the command should execute
			 * @param args The arguments the user entered
			 * @return true The command ran successfully
			 * @return false The command ran with issues
			 */
			virtual bool onExecute(const std::vector<String>& args) = 0;

			/**
			 * @brief Returns the name of the command that has to be entered after the command prefix (non case sensitive)
			 * @return String The name
			 */
			virtual String getName() const = 0;

			/**
			 * @brief Will later be used to determine if command executor has enough permissions
			 * @return true Command can be run
			 * @return false Insufficient Permissions
			 */
			virtual bool canRunCommand() const = 0;
		};
	}
}
