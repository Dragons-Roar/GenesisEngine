#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/UUID.hpp"
#include "GenesisCore/world/generator/WorldGenerator.hpp"

namespace ge {
	namespace core {
		class Chunk;
		class ChunkColumn;
		
		class World {
		public:
			struct Data {
				Data(const String& name): name(name), uuid(UUID()) {}

				String name;
				UUID uuid;
			};

			World(const String& name, WorldGenerator* generator);
			~World();

			void setVoxel(Voxel voxel, int32 x, int32 y, int32 z) { setVoxel(voxel, 0, VoxelWorldPos{x, y, z}); }
			void setVoxel(Voxel voxel, Meta meta, int32 x, int32 y, int32 z) { setVoxel(voxel, meta, VoxelWorldPos{x, y, z}); }
			void setVoxel(Voxel voxel, const VoxelWorldPos& pos) { setVoxel(voxel, 0, pos); }
			void setVoxel(Voxel voxel, Meta meta, const VoxelWorldPos& pos);

			void setMeta(Meta meta, int32 x, int32 y, int32 z) { setMeta(meta, VoxelWorldPos{x, y, z}); }
			void setMeta(Meta meta, const VoxelWorldPos& pos);

			void createChunkColumn(const ChunkPos& pos);
			ChunkColumn* getColumn(const ChunkPos& pos);

			std::list<std::pair<const ChunkPos, ChunkColumn*>>::const_iterator begin() const { return chunks.begin(); }
			std::list<std::pair<const ChunkPos, ChunkColumn*>>::const_iterator end() const { return chunks.end(); }

		protected:
			std::unordered_map<ChunkPos, ChunkColumn*> chunks;
			Data* meta;
			WorldGenerator* generator;
		};
	}
}
