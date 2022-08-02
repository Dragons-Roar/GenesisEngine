#pragma once
#include "./Defines.hpp"

namespace ge {
	namespace core {
		class UInt8 {
		public:
			UInt8() = delete;

			static uint8 parse(const std::string& str);
		};

		class UInt16 {
		public:
			UInt16() = delete;

			static uint16 parse(const std::string& str);
		};

		class UInt32 {
		public:
			UInt32() = delete;

			static uint32 parse(const std::string& str);
		};

		class UInt64 {
		public:
			UInt64() = delete;

			static uint64 parse(const std::string& str);
		};
	}
}
