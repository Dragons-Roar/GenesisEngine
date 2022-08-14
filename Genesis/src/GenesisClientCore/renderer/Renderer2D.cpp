#include "GenesisClientCore/renderer/Buffer.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include "Renderer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ge {
	namespace clientcore {
		struct QuadVertex {
			glm::vec3 pos;
			glm::vec2 uv;
			glm::vec4 color;
		};

		struct Renderer2DData {
			const uint32 maxQuads = 10000;
			const uint32 maxVertices = maxQuads * 4;
			const uint32 maxIndices = maxQuads * 6;

			ge::core::Ref<IVertexArray> quadVertexArray;
			ge::core::Ref<IVertexBuffer> quadVertexBuffer;
			ge::core::Ref<Texture2D> whiteTexture;
			ge::core::Ref<IShader> texturedShader;

			uint32 quadIndexCount = 0;
			QuadVertex* quadVertexBufferBase = nullptr;
			QuadVertex* quadVertexBufferPtr = nullptr;
		};

		static Renderer2DData* data;

		void Renderer2D::init() {
			GE_ProfileFunction();

			data = new Renderer2DData();

			data->quadVertexArray = IVertexArray::create();
			data->quadVertexBuffer = IVertexBuffer::create(data->maxVertices * sizeof(QuadVertex));
			data->quadVertexBuffer->setLayout({
			    {ShaderDataType::FLOAT3, "a_pos"  },
			    {ShaderDataType::FLOAT2, "a_uv"   },
			    {ShaderDataType::FLOAT4, "a_color"}
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
			data->texturedShader->setUniform2f("u_tiling", glm::vec2(1.f));
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
		}
		void Renderer2D::endScene() {
			GE_ProfileFunction();

			size_t dataSize = (uint8*) data->quadVertexBufferPtr - (uint8*) data->quadVertexBufferBase;
			data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

			flush();
		}
		void Renderer2D::flush() {
			GE_ProfileFunction();

			data->whiteTexture->bind();
			RenderCommand::drawIndexed(data->quadVertexArray, data->quadIndexCount);
		}

		void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const glm::vec2& tiling) {
			GE_ProfileFunction();

			data->quadVertexBufferPtr->pos = pos;
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 0.f};
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 0.f};
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 1.f};
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 1.f};
			data->quadVertexBufferPtr++;
			data->quadIndexCount += 6;

			/*data->texturedShader->setUniform2f("u_tiling", tiling);
			data->whiteTexture->bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
			data->texturedShader->setUniformMatrix4fv("u_transformMatrix", transform);

			data->quadVertexArray->bind();
			RenderCommand::drawIndexed(data->quadVertexArray);*/
		}
		void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color, const glm::vec2& tiling) {
			GE_ProfileFunction();

			data->texturedShader->setUniform4f("u_color", color);
			data->texturedShader->setUniform2f("u_tiling", tiling);
			texture->bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
			data->texturedShader->setUniformMatrix4fv("u_transformMatrix", transform);

			data->quadVertexArray->bind();
			RenderCommand::drawIndexed(data->quadVertexArray);
		}

		void Renderer2D::drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float32 rotation, const glm::vec2& tiling) {
			GE_ProfileFunction();

			data->texturedShader->setUniform4f("u_color", color);
			data->texturedShader->setUniform2f("u_tiling", tiling);
			data->whiteTexture->bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * glm::rotate(glm::mat4(1.f), rotation, glm::vec3(0.f, 0.f, 1.f)) * glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
			data->texturedShader->setUniformMatrix4fv("u_transformMatrix", transform);

			data->quadVertexArray->bind();
			RenderCommand::drawIndexed(data->quadVertexArray);
		}
		void Renderer2D::drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color, const glm::vec2& tiling) {
			GE_ProfileFunction();

			data->texturedShader->setUniform4f("u_color", color);
			data->texturedShader->setUniform2f("u_tiling", tiling);
			texture->bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * glm::rotate(glm::mat4(1.f), rotation, glm::vec3(0.f, 0.f, 1.f)) * glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
			data->texturedShader->setUniformMatrix4fv("u_transformMatrix", transform);

			data->quadVertexArray->bind();
			RenderCommand::drawIndexed(data->quadVertexArray);
		}
	}
}
