#pragma once
#include "./Defines.hpp"

namespace ge {
	namespace core {
		class UInt8 {
		public:
			static uint8 parse(const std::string& str);
		};

		class UInt16 {
		public:
			static uint16 parse(const std::string& str);
		};

		class UInt32 {
		public:
			static uint32 parse(const std::string& str);
		};

		class UInt64 {
		public:
			static uint64 parse(const std::string& str);
		};
	}
}
