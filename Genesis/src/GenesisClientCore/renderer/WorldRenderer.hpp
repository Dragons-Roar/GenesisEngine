#pragma once
#include <GenesisCore/world/World.hpp>

#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisClientCore/registry/BlockData.hpp"

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
			};

			static void init();
			static void shutdown();

			static void addToDrawable(const ChunkPos& pos);
			static void createNewData();
			static void flush();

			static void beginWorld(ge::core::World* world);

			static void beginScene(const PerspectiveCamera& camera);
			static void updateChunks();
			static void renderVoxel(const VoxelWorldPos& pos, const BlockData& d);

			static void drawChunks();

			static Data* data;
		};
	}
}
