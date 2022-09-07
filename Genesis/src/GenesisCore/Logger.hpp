#pragma once
#include "GenesisCore/Defines.hpp"
#include <spdlog/spdlog.h>

namespace ge {
	namespace core {
		class Logger {
		public:
			static void init();
			static void dispose();

			inline static std::shared_ptr<spdlog::logger>& getLogger() { return logger; }

		private:
			static std::shared_ptr<spdlog::logger> logger;
		};
	}
}

#ifndef GE_DIST
#	define GE_Info(...) SPDLOG_INFO(__VA_ARGS__)
#	define GE_Warn(...) SPDLOG_WARN(__VA_ARGS__)
#	define GE_Error(...) SPDLOG_ERROR(__VA_ARGS__)
#	define GE_Fatal(...) SPDLOG_CRITICAL(__VA_ARGS__)
#else
#	define GE_Info(...) SPDLOG_INFO(__VA_ARGS__)
#	define GE_Warn(...) SPDLOG_WARN(__VA_ARGS__)
#	define GE_Error(...) SPDLOG_ERROR(__VA_ARGS__)
#	define GE_Fatal(...) SPDLOG_CRITICAL(__VA_ARGS__)
#endif

#ifndef GE_DIST
#	define GE_Assert(x, ...)                                      \
		{                                                          \
			if(!(x)) {                                             \
				GE_Fatal("Assertion Triggered: {0}", __VA_ARGS__); \
				__debugbreak();                                    \
			}                                                      \
		}
#else
#	define GE_Assert(x, ...)
#endif

/// Throw a exception of type ge::core::GenesisRuntimeException and print to console
#define GE_ThrowException(e)                                     \
	{                                                            \
		ge::core::exceptions::GenesisRuntimeException::print(e); \
		throw e;                                                 \
	}
#pragma once
