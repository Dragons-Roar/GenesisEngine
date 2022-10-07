#include "GenesisClientCore/WorldGenerator.hpp"
#include "GenesisClientCore/registry/Registry.hpp"
#include <GenesisCore/world/ChunkColumn.hpp>
#include <GenesisCore/world/Chunk.hpp>

namespace ge {
	namespace clientcore {
		void WorldGenerator::generate(ge::core::ChunkColumn* chunk) {
			ChunkPos pos = chunk->getChunkPos();

			for(uint8 x = 0; x < GE_CHUNK_SIZE; ++x) {
				for(uint8 z = 0; z < GE_CHUNK_SIZE; ++z) {
					if((pos.x % 2 == 0 && pos.y % 2 == 0) || (pos.x % 2 != 0 && pos.y % 2 != 0)) {
						chunk->setVoxel(Registry::getBlockByKey("magenta").getID(), x, 20, z);
					} else {
						chunk->setVoxel(Registry::getBlockByKey("blue").getID(), x, 20, z);
					}
				}
			}
		}
	}
}
