#include "WorldRenderer.hpp"

#include "GenesisClientCore/renderer/RenderCommand.hpp"

constexpr float32 GE_VOXEL_SIZE = 1.f;

namespace ge {
	namespace clientcore {
		WorldRenderer::Data* WorldRenderer::data = nullptr;

		void WorldRenderer::init() {
			GE_ProfileFunction();

			GE_Info("Initializing World Renderer...");

			data = new Data();
			data->worldShader = IShader::create("assets/shader/3d/basic.glsl");
			data->vertexArray = IVertexArray::create();
			data->vertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(Vertex));
			data->vertexBuffer->setLayout({
				{ ShaderDataType::FLOAT3, "a_pos" },
				{ ShaderDataType::FLOAT2, "a_uv" },
				{ ShaderDataType::FLOAT4, "a_color" }
			});
			data->vertexArray->addVertexBuffer(data->vertexBuffer);

			data->base = new Vertex[data->maxVertices];

			uint32* quadIndices = new uint32[data->maxIndices];
			uint32 offset = 0;
			for(uint32 i = 0; i < data->maxIndices; i += 6) {
				quadIndices[i + 0] = offset + 0;
				quadIndices[i + 1] = offset + 1;
				quadIndices[i + 2] = offset + 2;

				quadIndices[i + 3] = offset + 2;
				quadIndices[i + 4] = offset + 3;
				quadIndices[i + 5] = offset + 0;

				offset += 4;
			}

			ge::core::Ref<IIndexBuffer> quadIndexBuffer = IIndexBuffer::create(quadIndices, data->maxIndices);
			data->vertexArray->setIndexBuffer(quadIndexBuffer);
			delete[] quadIndices;

			flush();
		}
		void WorldRenderer::shutdown() {
			GE_ProfileFunction();

			GE_Info("Shutting down WorldRenderer...");
			delete data;
		}

		void WorldRenderer::flush() {
			GE_ProfileFunction();

			data->current = data->base;
		}
		void WorldRenderer::draw() {
			GE_ProfileFunction();

			size_t size = (uint8*) data->current - (uint8*) data->base;
			data->vertexBuffer->setData(data->base, size);

			RenderCommand::drawIndexed(data->vertexArray, data->indexCount);
		}

		void WorldRenderer::beginScene(const PerspectiveCamera& camera) {
			GE_ProfileFunction();

			data->worldShader->bind();
			data->worldShader->setUniformMatrix4fv("u_viewProjectionMatrix", camera.getViewProjectionMatrix());
		}
		void WorldRenderer::endScene() {
			GE_ProfileFunction();

			draw();
			flush();
		}

		void WorldRenderer::renderColumn(ge::core::ChunkColumn* c) {
			GE_ProfileFunction();

			// ---> Front Face <--- //
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;

			// ---> Back Face (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(0.f, 0.f, 1.f, 1.f);
			data->current++;

			// ---> Right Face <--- //
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;

			// ---> Left Face (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			data->current++;

			// ---> Top <--- //
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;

			// ---> Bottom (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f);
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f);
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE);
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = glm::vec4(0.f, 1.f, 0.f, 1.f);
			data->current++;

			data->indexCount += 36;
		}
	}
}
