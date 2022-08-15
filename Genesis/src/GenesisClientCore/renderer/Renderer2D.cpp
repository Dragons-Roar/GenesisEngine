#include "GenesisClientCore/renderer/Buffer.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include "Renderer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ge {
	namespace clientcore {
		Renderer2D::Data* Renderer2D::data = nullptr;

		void Renderer2D::init() {
			GE_ProfileFunction();

			data = new Data();

			data->quadVertexArray = IVertexArray::create();
			data->quadVertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(QuadVertex));
			data->quadVertexBuffer->setLayout({
			    {ShaderDataType::FLOAT3, "a_pos"   },
			    {ShaderDataType::FLOAT2, "a_uv"    },
			    {ShaderDataType::FLOAT4, "a_color" },
			    {ShaderDataType::FLOAT2, "a_tiling"}
            });
			data->quadVertexArray->addVertexBuffer(data->quadVertexBuffer);

			data->quadVertexBufferBase = new QuadVertex[data->maxVertices];

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

			ge::core::Ref<IIndexBuffer> quadIB = IIndexBuffer::create(quadIndices, data->maxIndices);
			data->quadVertexArray->setIndexBuffer(quadIB);
			delete[] quadIndices;

			data->whiteTexture = Texture2D::create(1, 1);
			uint32 whiteTextureData = 0xFFFFFFFF;
			data->whiteTexture->setData(&whiteTextureData, sizeof(uint32));

			data->texturedShader = IShader::create("assets/shader/textured.glsl");
			data->texturedShader->bind();

			data->texturedShader->setUniform1i("u_texture", 0);

			data->quadVertexPositions[0] = {-0.5f, -0.5f, 0.f, 1.f};
			data->quadVertexPositions[1] = {0.5f, -0.5f, 0.f, 1.f};
			data->quadVertexPositions[2] = {0.5f, 0.5f, 0.f, 1.f};
			data->quadVertexPositions[3] = {-0.5f, 0.5f, 0.f, 1.f};

			flush();
		}
		void Renderer2D::shutdown() {
			delete data;
		}

		void Renderer2D::beginScene(const OrthographicCamera& camera) {
			GE_ProfileFunction();

			data->texturedShader->bind();
			data->texturedShader->setUniformMatrix4fv("u_viewProjectionMatrix", camera.getViewProjectionMatrix());

			data->quadIndexCount = 0;
			data->quadVertexBufferPtr = data->quadVertexBufferBase;

			data->texture = nullptr;

			flush();
		}
		void Renderer2D::endScene() {
			GE_ProfileFunction();

			draw();
			flush();
		}

		void Renderer2D::flush() {
			GE_ProfileFunction();

			data->quadIndexCount = 0;
			data->quadVertexBufferPtr = data->quadVertexBufferBase;
			data->texture = nullptr;
		}
		void Renderer2D::draw() {
			GE_ProfileFunction();

			size_t dataSize = (uint8*) data->quadVertexBufferPtr - (uint8*) data->quadVertexBufferBase;
			data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

			data->texture->bind();
			RenderCommand::drawIndexed(data->quadVertexArray, data->quadIndexCount);
			data->stats.drawCalls++;
		}

		void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color, const glm::vec2& tiling) {
			GE_ProfileFunction();

			if(data->texture == nullptr) data->texture = texture;
			if(data->quadIndexCount >= data->maxIndices || data->texture != texture) {
				draw();
				flush();
			}

			data->quadVertexBufferPtr->pos = pos;
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;
			data->quadIndexCount += 6;

			data->stats.quadCount++;
		}

		void Renderer2D::drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color, const glm::vec2& tiling) {
			GE_ProfileFunction();

			if(data->texture == nullptr) data->texture = texture;
			if(data->quadIndexCount >= data->maxIndices || data->texture != texture) {
				draw();
				flush();
			}

			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * glm::rotate(glm::mat4(1.f), rotation, {0.f, 0.f, 1.f}) * glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});

			data->quadVertexBufferPtr->pos = transform * data->quadVertexPositions[0];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = transform * data->quadVertexPositions[1];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = transform * data->quadVertexPositions[2];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = transform * data->quadVertexPositions[3];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;
			data->quadIndexCount += 6;

			data->stats.quadCount++;
		}

		void Renderer2D::resetStats() {
			memset(&data->stats, 0, sizeof(Renderer2D::Stats));
		}
		Renderer2D::Stats Renderer2D::getStats() {
			return data->stats;
		}
	}
}
