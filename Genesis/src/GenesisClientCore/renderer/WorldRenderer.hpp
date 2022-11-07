#pragma once
#include <GenesisCore/Location.hpp>
#include <GenesisCore/world/World.hpp>

#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/registry/BlockData.hpp"
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"

namespace ge {
	namespace clientcore {
		class WorldRenderer {
		public:
			struct Vertex {
				glm::vec3 pos;
				glm::vec2 uv;
				glm::vec4 color;
			};

			struct ChunkDrawData {
				ge::core::Ref<IVertexArray> array;
				uint32 indicesCount;
			};

			struct Data {
				Data() {}

				/// @brief The max vertices per chunk
				const uint32 maxVertices = 800000;
				const uint32 maxIndices = maxVertices * 6;

				ge::core::Ref<IShader> worldShader;

				ge::core::Ref<IVertexArray> vertexArray;
				ge::core::Ref<IVertexBuffer> vertexBuffer;

				uint32 indexCount;
				Vertex* base;
				Vertex* current;

				ge::core::World* world;
				std::vector<ge::core::Chunk*> chunkUpdates;
				std::unordered_map<ChunkPos, ChunkDrawData> chunkDrawables;

				ChunkPos lastChunkPos;

				/// @brief Stores chunks that are POTENTIALLY visible
				std::vector<ChunkPos> chunkVisibleList;
				std::vector<ChunkPos> oldChunKVisibleList;

				std::vector<ChunkPos> chunkDropList;
			};

			struct Stats {
				uint32 chunkCount = 0;
			};

			/// @brief Initializes the world renderer
			static void init();
			/// @brief Destorys the world renderer
			static void shutdown();

		public:
			/// @brief Begins a new word
			static void beginWorld(ge::core::World* world);

			/**
			 * @brief Begins a new scene using to before bound world
			 * @param camera The camera used to "capture" the graphics
			 */
			static void beginScene(const PerspectiveCamera& camera);
			/// @brief Searches for dirty chunks and updates them in beginScene()
			static void updateChunks();
			/// @brief Draws chunks to the render target
			static void drawChunks();
			/// @brief Clears current render stats
			static void clearStats();
			/// @brief Get current render stats
			/// @return const ge::core::Ref<Stats>
			static const ge::core::Ref<Stats> getStats() { return stats; }

		private:
			/// @brief Add chunk to current drawable
			static void addToDrawable(const ChunkPos& pos);
			/// @brief Resets the render data and intializes it to prepare for next frame
			static void createNewData();
			/// @brief Flushes the data to the gpu
			static void flush();
			/**
			 * @brief Adds a new voxel to the current updating chunk
			 * @param pos Ths pos of the voxel (in world coordiantes)
			 * @param d The data of the voxel
			 */
			static void renderVoxel(const VoxelWorldPos& pos, const BlockData& d);

			/// @brief Removes a chunk from the drawables
			static void dropChunk(const ChunkPos& pos);

			static Data* data;
			static ge::core::Ref<Stats> stats;
		};
	}
}
