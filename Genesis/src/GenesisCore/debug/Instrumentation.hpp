#pragma once
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

typedef std::string String;

namespace ge {
	namespace core {

		struct ProfileResult {
			String name;
			long long start, end;
			uint32_t threadID;
		};

		struct InstrumentationSession {
			String name;
		};

		class Instrumentor {
		private:
			InstrumentationSession *currentSession;
			std::ofstream outputStream;
			int ProfileCount;

		public:
			Instrumentor() : currentSession(nullptr), ProfileCount(0) {}

			void beginSession(const String &name, const String &filepath = "results.json") {
				outputStream.open(filepath);
				writeHeader();
				currentSession = new InstrumentationSession{name};
			}

			void endSession() {
				writeFooter();
				outputStream.close();
				delete currentSession;
				currentSession = nullptr;
				ProfileCount = 0;
			}

			void writeProfile(const ProfileResult &result) {
				if (ProfileCount++ > 0)
					outputStream << ",";

				String name = result.name;
				std::replace(name.begin(), name.end(), '"', '\'');

				outputStream << "{";
				outputStream << "\"cat\":\"function\",";
				outputStream << "\"dur\":" << (result.end - result.start) << ',';
				outputStream << "\"name\":\"" << name << "\",";
				outputStream << "\"ph\":\"X\",";
				outputStream << "\"pid\":0,";
				outputStream << "\"tid\":" << result.threadID << ",";
				outputStream << "\"ts\":" << result.start;
				outputStream << "}";

				outputStream.flush();
			}

			void writeHeader() {
				outputStream << "{\"otherData\": {},\"traceEvents\":[";
				outputStream.flush();
			}

			void writeFooter() {
				outputStream << "]}";
				outputStream.flush();
			}

			static Instrumentor &get() {
				static Instrumentor instance;
				return instance;
			}
		};

		class InstrumentationTimer {
		public:
			InstrumentationTimer(const char *name) : name(name), stopped(false) {
				startTimepoint = std::chrono::high_resolution_clock::now();
			}

			~InstrumentationTimer() {
				if (!stopped)
					stop();
			}

			void stop() {
				auto endTimepoint = std::chrono::high_resolution_clock::now();

				long long start = std::chrono::time_point_cast<std::chrono::microseconds>(
				                      startTimepoint)
				                      .time_since_epoch()
				                      .count();
				long long end =
				    std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
				        .time_since_epoch()
				        .count();

				uint32_t threadID = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
				Instrumentor::get().writeProfile({name, start, end, threadID});

				stopped = true;
			}

		private:
			const char *name;
			std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
			bool stopped;
		};
	}
}
