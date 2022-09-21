#pragma once
#include "GenesisCore/Defines.hpp"
#include "Dirty.hpp"

namespace ge {
	namespace core {
		class Chunk;
		class World;

		class ChunkColumn: public DirtyFlag {
		public:
			ChunkColumn(ChunkPos pos, World* world): pos(pos), world(world), DirtyFlag(true) { }
			~ChunkColumn();

			void setVoxel(Voxel voxel, uint8 x, uint16 y, uint8 z) { setVoxel(voxel, 0, x, y, z); }
			void setVoxel(Voxel voxel, Meta meta, uint8 x, uint16 y, uint8 z);

			void setMeta(Meta meta, uint8 x, uint16 y, uint8 z);

			const World* getWorld() const { return world; }
			World* getWorld() { return world; }

			Chunk* createChunk(uint8 pos);

			const ChunkPos& getChunkPos() const { return pos; }

			Chunk* chunks[GE_WORLD_HEIGHT];

		protected:
			ChunkPos pos;
			World* world;
		};
	}
}
