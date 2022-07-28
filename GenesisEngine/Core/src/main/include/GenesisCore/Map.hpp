#pragma once
#include <unordered_map>

namespace ge {
	namespace core {
		template<class K, class V>
		class Map {
		public:
			Map();
			Map(const Map& src);
			Map(Map&& src);
			~Map();

		private:
		};
	}
}
