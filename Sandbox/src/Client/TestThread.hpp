#pragma once
#include "GenesisCore/Logger.hpp"
#include "GenesisCore/threads/Thread.hpp"

namespace sb {
	class TestThread: public ge::core::Thread {
	public:
		TestThread(): ge::core::Thread("TestThread") {}

		void* run() override {
			GE_Info("Started!");
			ge::core::ThreadPool::printThreads();
			ge::core::ThisThread::sleepMS(5000);
			GE_Info("Finished!");
			return 0;
		}
	};
}
