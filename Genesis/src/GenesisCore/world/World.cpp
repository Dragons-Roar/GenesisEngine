#include "GenesisCore/world/World.hpp"
#include "GenesisCore/world/Chunk.hpp"
#include "GenesisCore/world/ChunkColumn.hpp"
#include "GenesisCore/Logger.hpp"

namespace ge {
	namespace core {
		World::World(const String& name, WorldGenerator* generator): generator(generator) {
			meta = new Data(name);
			GE_Info("Creating {} {}", meta->name, meta->uuid.format());
		}
		World::~World() {
			GE_Info("Deleting world... (" + meta->name + ", " + meta->uuid.format() + ")");
			for(auto it = chunks.begin(); it != chunks.end(); ++it) {
				ChunkPos pos = it->first;
				ChunkColumn* column = it->second;
				GE_Info("Deleting Chunk Column {}/{}...", pos.x, pos.y);
				delete column;
			}
			delete meta;
		}

		void World::setVoxel(Voxel voxel, Meta meta, const VoxelWorldPos& pos) {
			Chunk* chunk = chunks[ChunkPos(pos.x / GE_CHUNK_SIZE_F, pos.z / GE_CHUNK_SIZE_F)]->chunks[(uint16) (pos.y / GE_CHUNK_SIZE_F)];
			chunk->setVoxel(voxel, meta, VoxelChunkPos(pos.x % GE_CHUNK_SIZE, pos.y % GE_CHUNK_SIZE, pos.z % GE_CHUNK_SIZE));
		}
		void World::setMeta(Meta meta, const VoxelWorldPos& pos) {
			Chunk* chunk = chunks[ChunkPos(pos.x / GE_CHUNK_SIZE_F, pos.z / GE_CHUNK_SIZE_F)]->chunks[(uint16) (pos.y / GE_CHUNK_SIZE_F)];
			chunk->setMeta(meta, VoxelChunkPos(pos.x % GE_CHUNK_SIZE, pos.y % GE_CHUNK_SIZE, pos.z % GE_CHUNK_SIZE));
		}

		void World::createChunkColumn(const ChunkPos& pos) {
			ChunkColumn* column = new ChunkColumn(pos, this); 
			for(uint8 i = 0; i < GE_WORLD_HEIGHT; ++i) {
				column->createChunk(i);
				generator->generate(column);
			}

			chunks[pos] = column;
		}
		ChunkColumn* World::getColumn(const ChunkPos& pos) {
			if(chunks.find(pos) == chunks.end()) {
				//GE_Info("Creating column {} {}", pos.x, pos.y);
				createChunkColumn(pos);
			}
			return chunks[pos];
		}
	}
}
