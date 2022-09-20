#include "GenesisCore/Defines.hpp"
#include "Dirty.hpp"

namespace ge {
	namespace core {
		class ChunkColumn;

		class Chunk: public DirtyFlag {
		public:
			Chunk(uint8 pos, ChunkColumn* ChunkColumn): pos(pos), chunkColumn(chunkColumn) {}
			~Chunk();

			void setVoxel(Voxel voxel, uint8 x, uint8 y, uint8 z) { setVoxel(voxel, 0, VoxelChunkPos{x, y, z}); }
			void setVoxel(Voxel voxel, Meta meta, uint8 x, uint8 y, uint8 z) { setVoxel(voxel, meta, VoxelChunkPos{x, y, z}); }
			void setVoxel(Voxel voxel, const VoxelChunkPos& pos) { setVoxel(voxel, 0, pos); }
			void setVoxel(Voxel voxel, Meta meta, const VoxelChunkPos& pos);

			void setMeta(Meta meta, uint8 x, uint8 y, uint8 z) { setMeta(meta, VoxelChunkPos{x, y, z}); }
			void setMeta(Meta meta, const VoxelChunkPos& pos);

			Voxel getVoxel(uint8 x, uint8 y, uint8 z) const { return getVoxel(VoxelChunkPos{x, y, z}); }
			Voxel getVoxel(const VoxelChunkPos& pos) const { return voxels[pos.x][pos.y][pos.z]; }

			Voxel getMeta(uint8 x, uint8 y, uint8 z) const { return getMeta(VoxelChunkPos{x, y, z}); }
			Voxel getMeta(const VoxelChunkPos& pos) const { return metas[pos.x][pos.y][pos.z]; }
 
			/// @brief The voxels stored in this chunk (IMPORTANT: Voxels edited this way will not trigger a update / rerender)
			Voxel voxels[GE_CHUNK_SIZE][GE_CHUNK_SIZE][GE_CHUNK_SIZE] = { 0 };
			/// @brief The metas stored in this chunk (IMPORTANT: Metas edited this way will not trigger a update /rerender)
			Meta metas[GE_CHUNK_SIZE][GE_CHUNK_SIZE][GE_CHUNK_SIZE] = { 0 };
		
			const ChunkColumn* getChunkColumn() const { return chunkColumn; }
			ChunkColumn* getChunkColumn() { return chunkColumn; }

		protected:
			/// @brief A reference the the chunk column where this chunk is stored in
			ChunkColumn* chunkColumn;
			/// @brief The position (index) where this chunk lays in the chunk column
			uint8 pos;
		};
	}
}
