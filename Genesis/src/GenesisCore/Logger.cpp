#include <GenesisCore/Logger.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ge {
	namespace core {
		std::shared_ptr<spdlog::logger> Logger::logger;

		void Logger::init() {
			spdlog::set_pattern("<%T>[%^%l%$/%s:%#] %v");
			logger = spdlog::stdout_color_mt("Genesis");
			logger->set_level(spdlog::level::trace);
		}
		void Logger::dispose() {
		}
	}
}
