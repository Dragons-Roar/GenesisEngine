#pragma once
#include <GenesisCore/world/generator/WorldGenerator.hpp>
#include "GenesisClientCore/Defines.hpp"

namespace ge {
	namespace clientcore {
		class WorldGenerator: public ge::core::WorldGenerator {
		public:
			void generate(ge::core::ChunkColumn* chunk) override;
		};
	}
}
