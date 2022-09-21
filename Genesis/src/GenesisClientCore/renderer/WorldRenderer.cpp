#include "WorldRenderer.hpp"

#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/registry/Registry.hpp"
#include <GenesisCore/world/Chunk.hpp>
#include <GenesisCore/world/ChunkColumn.hpp>

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

			// Current hardcoded default value
			data->lastChunkPos = ChunkPos(-99, -99);

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

		void WorldRenderer::beginWorld(ge::core::World* world) {
			data->world = world;
		}

		void WorldRenderer::beginScene(const PerspectiveCamera& camera) {
			GE_ProfileFunction();

			data->worldShader->bind();
			data->worldShader->setUniformMatrix4fv("u_viewProjectionMatrix", camera.getViewProjectionMatrix());

			// Check for chunks that need to be loaded
			ge::core::Location loc = camera.getLocation();
			ChunkPos pos(loc.getX() / (float32) GE_CHUNK_SIZE, loc.getZ() / (float32) GE_CHUNK_SIZE);
			if(data->lastChunkPos != pos) {
				GE_Info("Player crossed chunk border! Searching for new chunks...");
				for(int32 x = pos.x - GE_RENDER_DISTANCE; x < pos.x + GE_RENDER_DISTANCE; ++x) {
					for(int32 z = pos.y - GE_RENDER_DISTANCE; z < pos.y + GE_RENDER_DISTANCE; ++z) {
						data->world->getColumn(ChunkPos(x, z));
					}
				}
			}

			data->lastChunkPos = pos;

			// Checking for dirty chunks and adding them to update list
			for(auto it = data->world->begin(); it != data->world->end(); ++it) {
				if(it->second->isDirty()) {
					for(uint8 i = 0; i < GE_WORLD_HEIGHT; i++) {
						// Adds dirty chunks to chunk updates and removes dirty flag from column aswell as chunks
						if(!it->second->chunks[i]->isDirty()) continue;
						data->chunkUpdates.push_back(it->second->chunks[i]);
						it->second->chunks[i]->setDirty(false);
					}
					it->second->setDirty(false);
				}
			}
		}

		void WorldRenderer::updateChunks() {
			if(data->chunkUpdates.size() > 0) {
				GE_Info("Processing {} chunk updates...", data->chunkUpdates.size());
			}

			data->indexCount = 0;

			for(ge::core::Chunk* chunk: data->chunkUpdates) {
				for(uint32 x = 0; x < GE_CHUNK_SIZE; ++x) {
					for(uint32 y = 0; y < GE_CHUNK_SIZE; ++y) {
						for(uint32 z = 0; z < GE_CHUNK_SIZE; ++z) {
							if(chunk->voxels[x][y][z] < 1) continue;
							renderVoxel(VoxelWorldPos(x + chunk->getChunkColumn()->getChunkPos().x * GE_CHUNK_SIZE, y + chunk->getPos() * GE_CHUNK_SIZE, z + chunk->getChunkColumn()->getChunkPos().y * GE_CHUNK_SIZE), Registry::getBlockByID(chunk->voxels[x][y][z]).getData());
						}
					}
				}

				if(data->indexCount < 1) continue;

				// Flush at the end to reset render data
				addToDrawable(chunk->getChunkColumn()->getChunkPos());
			}
			data->chunkUpdates.clear();
		}

		void WorldRenderer::addToDrawable(const ChunkPos& pos) {
			size_t size = (uint8*) data->current - (uint8*) data->base;
			data->vertexBuffer->setData(data->base, size);
			data->chunkDrawables[pos] = ChunkDrawData { data->vertexArray, data->indexCount };

			createNewData();
		}
		void WorldRenderer::createNewData() {
			data->vertexArray = IVertexArray::create();
			data->vertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(Vertex));
			data->vertexBuffer->setLayout({
				{ ShaderDataType::FLOAT3, "a_pos" },
				{ ShaderDataType::FLOAT2, "a_uv" },
				{ ShaderDataType::FLOAT4, "a_color" }
			});
			data->vertexArray->addVertexBuffer(data->vertexBuffer);

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
			data->indexCount = 0;

			flush();

			delete[] quadIndices;
		}

		void WorldRenderer::drawChunks() {
			for(auto it = data->chunkDrawables.begin(); it != data->chunkDrawables.end(); ++it) {
				RenderCommand::drawIndexed(it->second.array, it->second.indicesCount);
			}
		}

		void WorldRenderer::renderVoxel(const VoxelWorldPos& pos, const BlockData& d) {
			const glm::vec3 add = glm::vec3(pos) * GE_VOXEL_SIZE;
			const glm::vec4 color = d.color;

			// ---> Front Face <--- //
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			// ---> Back Face (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			// ---> Right Face <--- //
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			// ---> Left Face (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			// ---> Top <--- //
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, GE_VOXEL_SIZE, 0.f) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			// ---> Bottom (0 and 2 are swapped) <--- //
			data->current->pos = glm::vec3(0.f, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(1.f, 1.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(0.f, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(1.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, 0.f) + add;
			data->current->uv = glm::vec2(0.f, 0.f);
			data->current->color = color;
			data->current++;
			data->current->pos = glm::vec3(GE_VOXEL_SIZE, 0.f, GE_VOXEL_SIZE) + add;
			data->current->uv = glm::vec2(0.f, 1.f);
			data->current->color = color;
			data->current++;

			data->indexCount += 36;
		}
	}
}
