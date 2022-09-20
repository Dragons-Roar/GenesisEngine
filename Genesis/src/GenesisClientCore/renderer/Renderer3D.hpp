#pragma once
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/Texture.hpp"
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace clientcore {
		class IShader;
		class IVertexBuffer;

		/**
		 * @brief Pure static renderer class for rendering 3d scenes
		 */
		class Renderer3D {
		public:
			struct Data {
				ge::core::Ref<IShader> shader;
			};

			struct CubeVertex {
				glm::vec3 pos;
				glm::vec2 uv;
			};

			Renderer3D() = delete;

			static void init();
			static void shutdown();

			static void beginScene(const PerspectiveCamera& camera);
			static void drawCube(const glm::vec3& from, const glm::vec3& to, const glm::vec4& color);
			static void endScene();

		private:
			static Renderer3D::Data* data;
		};
	}
}
