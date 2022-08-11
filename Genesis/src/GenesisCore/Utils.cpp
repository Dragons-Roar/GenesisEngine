#include <GenesisCore/Utils.hpp>

namespace ge {
	namespace core {
		void Utils::splitString(List<String, size_t>& list, const String& str, char delim) {
			if(str.find(delim) == String::npos) { list.add(str); }
			std::stringstream ss(str);
			String item;
			while(std::getline(ss, item, delim)) {
				list.add(item);
			}
		}

		uint32 Utils::countChars(const String& str, char c) {
			uint32 out = 0;
			for(uint32 i = 0; i < str.size(); ++i) {
				if(str[i] == c) out++;
			}
			return out;
		}
	}
}
