#include "GenesisCore/Datatypes.hpp"

namespace ge {
	namespace core {
		/* ---> UInt8 <--- */
		uint8 UInt8::parse(const std::string& str) {
			return static_cast<uint8>(std::strtoul(str.c_str(), nullptr, 0));
		}

		/* ---> UInt16 <--- */
		uint16 UInt16::parse(const std::string& str) {
			return static_cast<uint16>(std::strtoul(str.c_str(), nullptr, 0));
		}

		/* ---> UInt32 <--- */
		uint32 UInt32::parse(const std::string& str) {
			return static_cast<uint32>(std::strtoul(str.c_str(), nullptr, 0));
		}

		/* ---> UInt64 <--- */
		uint64 UInt64::parse(const std::string& str) {
			return static_cast<uint64>(std::strtoull(str.c_str(), nullptr, 0));
		}
	}
}
