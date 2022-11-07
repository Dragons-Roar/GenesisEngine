#include "WorldRenderer.hpp"

#include "GenesisClientCore/registry/Registry.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include <GenesisCore/world/Chunk.hpp>
#include <GenesisCore/world/ChunkColumn.hpp>

namespace ge {
	namespace clientcore {
		WorldRenderer::Data* WorldRenderer::data = nullptr;
		ge::core::Ref<WorldRenderer::Stats> WorldRenderer::stats = ge::core::CreateRef<WorldRenderer::Stats>();

		void WorldRenderer::init() {
			GE_ProfileFunction();

			GE_Info("Initializing World Renderer...");

			data = new Data();
			data->chunkVisibleList = std::vector<ChunkPos>();
			data->oldChunKVisibleList = std::vector<ChunkPos>();
			data->chunkDropList = std::vector<ChunkPos>();
			data->worldShader = IShader::create("assets/shader/3d/basic.glsl");
			data->vertexArray = IVertexArray::create();
			data->vertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(Vertex));
			data->vertexBuffer->setLayout({
			    {ShaderDataType::FLOAT3, "a_pos"  },
			    {ShaderDataType::FLOAT2, "a_uv"   },
			    {ShaderDataType::FLOAT4, "a_color"}
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
			ChunkPos pos = loc.getChunkPos();
			if(data->lastChunkPos != pos) {
				GE_Info("Player crossed chunk border! Searching for new chunks...");
				GE_Info("Recalculating potentially visible chunks...");

				data->oldChunKVisibleList = std::vector(data->chunkVisibleList);

				data->chunkVisibleList.clear();
				data->chunkVisibleList.reserve(GE_RENDER_DISTANCE * GE_RENDER_DISTANCE);
				for(int16 x = pos.x - GE_RENDER_DISTANCE; x < pos.x + GE_RENDER_DISTANCE; ++x) {
					for(int16 z = pos.y - GE_RENDER_DISTANCE; z < pos.y + GE_RENDER_DISTANCE; ++z) {
						data->chunkVisibleList.push_back(ChunkPos(x, z));
					}
				}

				data->chunkDropList.clear();
				for(uint32 i = 0; i < data->oldChunKVisibleList.size(); ++i) {
					bool found = false;
					for(uint32 j = 0; j < data->chunkVisibleList.size(); ++j) {
						if(data->oldChunKVisibleList[i].x == data->chunkVisibleList[j].x && data->oldChunKVisibleList[i].y == data->chunkVisibleList[j].y) {
							found = true;
							break;
						}
					}

					if(!found) data->chunkDropList.push_back(data->oldChunKVisibleList[i]);
				}
			}

			data->lastChunkPos = pos;

			// Checking for dirty chunks and adding them to update list
			for(auto it = data->chunkVisibleList.begin(); it != data->chunkVisibleList.end(); ++it) {
				auto chunk = data->world->getColumn(ChunkPos(it->x, it->y));
				if(chunk->isDirty()) {
					for(uint8 i = 0; i < GE_WORLD_HEIGHT; ++i) {
						if(!chunk->chunks[i]->isDirty()) continue;
						data->chunkUpdates.push_back(chunk->chunks[i]);
						chunk->chunks[i]->setDirty(false);
					}
					chunk->setDirty(false);
				}
			}
		}

		void WorldRenderer::updateChunks() {
			GE_ProfileFunction();

			if(data->chunkDropList.size() > 0) {
				GE_Info("Processing {} chunk drops...", data->chunkUpdates.size());
			}
			for(auto it = data->chunkDropList.begin(); it != data->chunkDropList.end(); ++it) {
				dropChunk(ChunkPos(it->x, it->y));
			}
			data->chunkDropList.clear();

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
			GE_ProfileFunction();

			size_t size = (uint8*) data->current - (uint8*) data->base;
			data->vertexBuffer->setData(data->base, size);
			data->chunkDrawables[pos] = ChunkDrawData {data->vertexArray, data->indexCount};

			createNewData();
		}
		void WorldRenderer::createNewData() {
			GE_ProfileFunction();

			data->vertexArray = IVertexArray::create();
			data->vertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(Vertex));
			data->vertexBuffer->setLayout({
			    {ShaderDataType::FLOAT3, "a_pos"  },
			    {ShaderDataType::FLOAT2, "a_uv"   },
			    {ShaderDataType::FLOAT4, "a_color"}
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
			GE_ProfileFunction();

			for(auto it = data->chunkDrawables.begin(); it != data->chunkDrawables.end(); ++it) {
				stats->chunkCount++;
				RenderCommand::drawIndexed(it->second.array, it->second.indicesCount);
			}
		}

		void WorldRenderer::renderVoxel(const VoxelWorldPos& pos, const BlockData& d) {
			GE_ProfileFunction();

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

		void WorldRenderer::dropChunk(const ChunkPos& pos) {
			GE_Info("Dropping chunk at {}/{}", pos.x, pos.y);
			data->chunkDrawables.erase(pos);
		}

		void WorldRenderer::clearStats() {
			stats->chunkCount = 0;
		}
	}
}
