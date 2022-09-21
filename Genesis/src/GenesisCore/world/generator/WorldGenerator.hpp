#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		class ChunkColumn;

		class WorldGenerator {
		public:
			virtual void generate(ChunkColumn* column) = 0;
		};
	}
}
