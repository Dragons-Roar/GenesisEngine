#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		using ThreadID = std::thread::id;

		class ThisThread {
		public:
			ThisThread() = delete;

			/**
			 * @brief Lets this thread sleep for x ms
			 * @param dur The time in ms
			 */
			static void sleepMS(uint32 dur);
		};

		class Thread {
		public:
			Thread(const String& name = "Thread");
			virtual ~Thread();

			/**
			 * @brief Starts this thread
			 */
			bool start();
			/**
			 * @brief Trys to terminate this thread
			 */
			void stop();

			/**
			 * @brief Waits until this thread has finished
			 * @return false Thread was not running
			 * @return true Thread has exited
			 */
			bool wait();

			/**
			 * @brief Get the Thread Result (non blocking)
			 * @param[out] hasData True if the thread has stopped execution and returned data
			 * @return void*
			 */
			void* getThreadResult();

			String getName() { return name; }
			ThreadID getID() { return handle->get_id(); }
			bool isRunning() { return running; }

		protected:
			virtual void* run() = 0;

		private:
			static void threadProc(Thread* t);

			std::thread* handle;
			String name;

			std::mutex mutex;
			std::mutex mutexStartFinished;
			std::atomic<bool> requestStop;

			bool running;
			bool joinable;

			void* returnData;
		};

		using ThreadList = std::vector<Thread*>;

		/**
		 * @brief Used to store/organize running/stopped threads
		 */
		class ThreadPool {
		public:
			ThreadPool() = delete;

			static void regsiter(Thread* thread) { threads.push_back(thread); }
			static void unregister(Thread* thread) { threads.erase(std::remove(threads.begin(), threads.end(), thread), threads.end()); }
			static void shutdown();

			static void printThreads();
			static ThreadList* getThreads() { return &threads; }

		private:
			static ThreadList threads;
		};
	}
}
