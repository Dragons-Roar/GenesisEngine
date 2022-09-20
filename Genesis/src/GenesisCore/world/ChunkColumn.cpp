#include "ChunkColumn.hpp"
#include "GenesisCore/Logger.hpp"
#include "GenesisCore/world/Chunk.hpp"
#include "GenesisCore/world/World.hpp"

namespace ge {
	namespace core {
		ChunkColumn::~ChunkColumn() {
			for(uint32 i = 0; i < GE_WORLD_HEIGHT; ++i) {
				delete chunks[i];
			}
		}

		void ChunkColumn::setVoxel(Voxel voxel, Meta meta, uint8 x, uint16 y, uint8 z) {
			GE_Assert(y >= 0 && y < GE_WORLD_HEIGHT_BLOCKS, "Y Pos needs to be between 0 and max world height");
			chunks[y / GE_CHUNK_SIZE]->setVoxel(voxel, meta, x, y % GE_CHUNK_SIZE, z);
		}
		void ChunkColumn::setMeta(Meta meta, uint8 x, uint16 y, uint8 z) {
			GE_Assert(y >= 0 && y < GE_WORLD_HEIGHT_BLOCKS, "Y Pos needs to be between 0 and max world height");
			chunks[y / GE_CHUNK_SIZE]->setMeta(meta, x, y % GE_CHUNK_SIZE, z);
		}

		Chunk* ChunkColumn::createChunk(uint8 pos) {
			GE_Assert(pos >= 0 && pos < GE_WORLD_HEIGHT, "Pos needs to be between 0 and GE_WORLD_HEIGHT (" + std::to_string(GE_WORLD_HEIGHT) + ")");

			Chunk* chunk = new Chunk(pos, this);
			chunks[pos] = chunk;
			return chunk;
		}
	}
}
