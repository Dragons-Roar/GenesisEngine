#include "GenesisCore/threads/Thread.hpp"

#include "GenesisCore/Logger.hpp"
#include "GenesisCore/threads/Mutex.hpp"

namespace ge {
	namespace core {
		ThreadList ThreadPool::threads;

		/**************
		 * ThisThread *
		 **************/

		void
		ThisThread::sleepMS(uint32 dur) {
			std::this_thread::sleep_for(std::chrono::milliseconds(dur));
		}

		/**********
		 * Thread *
		 **********/

		Thread::Thread(const String& name): running(false), requestStop(false), returnData(nullptr), name(name) {
			ThreadPool::regsiter(this);
		}
		Thread::~Thread() {
			GE_Info("Destroying...");
			if(running) stop();
			ThreadPool::unregister(this);
			delete returnData;
		}

		bool Thread::start() {
			AutoLockMutex lock(mutex);
			if(running) return false;

			requestStop = false;
			mutexStartFinished.try_lock();

			try {
				handle = new std::thread(threadProc, this);
			} catch(const std::system_error& e) {
				GE_Info("Internal Error! {0}", e.what());
				return false;
			}

			while(!running) {
				ThisThread::sleepMS(1);
			}

			mutexStartFinished.unlock();
			joinable = true;

			return true;
		}
		void Thread::stop() {
			requestStop = true;
		}
		bool Thread::wait() {
			AutoLockMutex lock(mutex);
			if(!joinable) return false;

			handle->join();

			ThreadPool::unregister(this);
			delete handle;
			handle = nullptr;
			GE_Assert(running == false, "Thread is still running but should have been stopped!");

			joinable = false;
			return true;
		}
		void* Thread::getThreadResult() {
			return returnData;
		}

		void Thread::threadProc(Thread* t) {
			t->running = true;
			t->mutexStartFinished.lock();
			t->returnData = t->run();
			t->running = false;
			t->mutexStartFinished.unlock();
		}

		/**************
		 * ThreadPool *
		 **************/

		void ThreadPool::printThreads() {
			if(threads.size() < 1) {
				GE_Info("No thread is currently registered!");
			} else {
				GE_Info("--- {0} Threads Registered ---", threads.size());
				for(Thread* t: threads) {
					GE_Info("Name: '{0}', ID: {1}, Has Return Data: {2}, Running: {3}", t->getName(), std::hash<std::thread::id> {}(t->getID()), t->getThreadResult() != nullptr, t->isRunning());
				}
			}
		}

		void ThreadPool::shutdown() {
			for(Thread* t: threads) {
				GE_Info("Deleting thread {0}...", t->getName());
				t->stop();
				GE_Info("Wating for thread to finish");
				t->wait();
				delete t;
				GE_Info("Destoryed!");
			}
		}
	}
}
