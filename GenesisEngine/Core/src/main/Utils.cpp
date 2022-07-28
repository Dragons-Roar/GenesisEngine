#include <GenesisCore/Utils.hpp>

namespace ge {
	namespace core {
		void Utils::splitString(List<String, size_t>& list, const String& str, char delim) {
			std::stringstream ss(str);
			String item;
			while(std::getline(ss, item, delim)) {
				list.add(item);
			}
		}
	}
}
