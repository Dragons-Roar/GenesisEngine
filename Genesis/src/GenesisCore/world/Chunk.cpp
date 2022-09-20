#include "Chunk.hpp"
#include "GenesisCore/Logger.hpp"
#include "GenesisCore/world/ChunkColumn.hpp"

namespace ge {
	namespace core {
		Chunk::~Chunk() {
		}

		void Chunk::setVoxel(Voxel voxel, Meta meta, const VoxelChunkPos& pos) {
			GE_Assert(pos.x < GE_CHUNK_SIZE && pos.x >= 0, "PosX must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");
			GE_Assert(pos.y < GE_CHUNK_SIZE && pos.y >= 0, "PosY must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");
			GE_Assert(pos.z < GE_CHUNK_SIZE && pos.z >= 0, "PosZ must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");

			voxels[pos.x][pos.y][pos.z] = voxel;
			metas[pos.x][pos.y][pos.z] = meta;
			chunkColumn->setDirty();
			dirty = true;
		}
		void Chunk::setMeta(Meta meta, const VoxelChunkPos& pos) {
			GE_Assert(pos.x < GE_CHUNK_SIZE && pos.x >= 0, "PosX must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");
			GE_Assert(pos.y < GE_CHUNK_SIZE && pos.y >= 0, "PosY must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");
			GE_Assert(pos.z < GE_CHUNK_SIZE && pos.z >= 0, "PosZ must be between 0 and GE_CHUNK_SIZE (" + std::to_string(GE_CHUNK_SIZE) + ")");

			metas[pos.x][pos.y][pos.z] = meta;
			dirty = true;
		}
	}
}
