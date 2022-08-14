#pragma once
#include "Defines.hpp"

namespace ge {
	namespace core {
		class Timer {
		public:
			Timer(const char* name): stopped(false), name(name) {
				startPoint = std::chrono::high_resolution_clock::now();
			}
			~Timer() { if(!stopped) stop(); }

			void stop() {
				auto endPoint = std::chrono::high_resolution_clock::now();
				uint64 start = std::chrono::time_point_cast<std::chrono::milliseconds>(startPoint).time_since_epoch().count();
				uint64 end = std::chrono::time_point_cast<std::chrono::milliseconds>(endPoint).time_since_epoch().count();

				stopped = true;
				std::cout << "Duration: " << (end - start) << "ms (" << name << ")" << std::endl;
			}

		private:
			bool stopped;
			std::chrono::time_point<std::chrono::steady_clock> startPoint;
			const char* name;
		};
	}
}
