#pragma once
#include <GenesisCore/world/ChunkColumn.hpp>

#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"

namespace ge {
	namespace clientcore {
		class WorldRenderer {
		public:
			struct Vertex {
				glm::vec3 pos;
				glm::vec2 uv;
				glm::vec4 color;
			};

			struct Data {
				const uint32 maxVertices = 50000;
				const uint32 maxIndices = maxVertices * 6;
				
				ge::core::Ref<IShader> worldShader;

				ge::core::Ref<IVertexArray> vertexArray;
				ge::core::Ref<IVertexBuffer> vertexBuffer;

				uint32 indexCount;
				Vertex* base;
				Vertex* current;
			};

			static void init();
			static void shutdown();

			static void draw();
			static void flush();

			static void beginScene(const PerspectiveCamera& camera);
			static void renderColumn(ge::core::ChunkColumn* c);
			static void endScene();

			static Data* data;
		};
	}
}
