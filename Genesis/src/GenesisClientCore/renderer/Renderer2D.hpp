#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/Texture.hpp"

namespace ge {
	namespace clientcore {
		class IVertexArray;
		class IVertexBuffer;
		class IShader;

		/**
		 * @brief Pure static renderer class for rendering 2D objects
		 */
		class Renderer2D {
		public:
			struct Stats {
				uint32 quadCount;
				uint32 drawCalls;

				uint32 getVertexCount() const { return quadCount * 4; }
				uint32 getIndicesCount() const { return quadCount * 6; }
			};

			struct QuadVertex {
				glm::vec3 pos;
				glm::vec2 uv;
				glm::vec4 color;
				glm::vec2 tiling;
			};

			struct Data {
				Renderer2D::Stats stats;

				const uint32 maxQuads = 50000;
				const uint32 maxVertices = maxQuads * 4;
				const uint32 maxIndices = maxQuads * 6;
				static const uint32 maxTextureSlots = 32;

				ge::core::Ref<IVertexArray> quadVertexArray;
				ge::core::Ref<IVertexBuffer> quadVertexBuffer;
				ge::core::Ref<Texture2D> whiteTexture;
				ge::core::Ref<IShader> texturedShader;

				uint32 quadIndexCount = 0;
				QuadVertex* quadVertexBufferBase = nullptr;
				QuadVertex* quadVertexBufferPtr = nullptr;

				ge::core::Ref<Texture2D> texture = nullptr;

				glm::vec4 quadVertexPositions[4];
			};

			Renderer2D() = delete;

			static void init();
			static void shutdown();
			static void flush();

			static void beginScene(const OrthographicCamera& camera);
			static void endScene();

			// Primitives
			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) { drawQuad({pos.x, pos.y, 0.f}, size, color); }
			static inline void drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color) { drawQuad(pos, size, data->whiteTexture, color, {1.f, 1.f}); }

			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f}) { drawQuad({pos.x, pos.y, 0.f}, size, texture, color, tiling); }
			static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f});

			static inline void drawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float32 rotation, const glm::vec2& tiling = {1.f, 1.f}) { drawQuadRotated({pos.x, pos.y, 0.f}, size, color, rotation, tiling); }
			static inline void drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float32 rotation, const glm::vec2& tiling = {1.f, 1.f}) { drawQuadRotated(pos, size, data->whiteTexture, rotation, color, tiling); }

			static inline void drawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f}) { drawQuadRotated({pos.x, pos.y, 0.f}, size, texture, rotation, color, tiling); }
			static void drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f});

			static void resetStats();
			static Stats getStats();

		private:
			static Renderer2D::Data* data;

			static void draw();
		};
	}
}
