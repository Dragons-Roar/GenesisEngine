#pragma once
#include "GenesisCore/command/impl/CommadThreads.hpp"
#include "GenesisCore/threads/Thread.hpp"

namespace ge {
	namespace core {
		class CommandThread: public Command {
		public:
			bool onExecute(const std::vector<String>& args) override {
				ge::core::ThreadPool::printThreads();
				return true;
			}
			String getName() const override {
				return "threads";
			}
			bool canRunCommand() const override {
				return true;
			}
		};
	}
}
