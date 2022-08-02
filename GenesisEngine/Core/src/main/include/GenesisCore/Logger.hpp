#pragma once
#include "./Defines.hpp"
#include "./GenesisBase.hpp"

// This file will be implemented later on!

namespace ge {
	namespace core {
		class Logger: public GClass {
		public:
			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::Logger";
				return ss.str();
			}
		};
	}
}

/// Throw a exception of type ge::core::GenesisRuntimeException and print to console
#define GE_ThrowException(e) std::cerr << e.toString() << std::endl; throw e
