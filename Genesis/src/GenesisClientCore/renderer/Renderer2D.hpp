#pragma once

#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/Texture.hpp"

namespace ge {
	namespace clientcore {
		/**
		 * @brief Pure static renderer class for rendering 2D objects
		 */
		class Renderer2D {
		public:
			Renderer2D() = delete;

			static void init();
			static void shutdown();
			static void flush();

			static void beginScene(const OrthographicCamera& camera);
			static void endScene();

			// Primitives
			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) { drawQuad({pos.x, pos.y, 0.f}, size, color); }
			static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f}) { drawQuad({pos.x, pos.y, 0.f}, size, texture, color, tiling); }
			static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f});

			static inline void drawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float32 rotation, const glm::vec2& tiling = {1.f, 1.f}) { drawQuadRotated({pos.x, pos.y, 0.f}, size, color, rotation, tiling); }
			static void drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float32 rotation, const glm::vec2& tiling = {1.f, 1.f});

			static inline void drawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f}) { drawQuadRotated({pos.x, pos.y, 0.f}, size, texture, rotation, color, tiling); }
			static void drawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const ge::core::Ref<Texture2D>& texture, float32 rotation, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}, const glm::vec2& tiling = {1.f, 1.f});

			struct Stats {
				uint32 drawCalls = 0;
				uint32 quadCount = 0;

				uint32 getVertexCount() { return quadCount * 4; }
				uint32 getIndexCount() { return quadCount * 6; }
			};
			static void resetStats();
			static Stats getStats();

		private:
			static void startNewBatch();
		};
	}
}
