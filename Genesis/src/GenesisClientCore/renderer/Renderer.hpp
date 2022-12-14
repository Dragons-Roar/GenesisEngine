#pragma once
#include "GenesisClientCore/renderer/RendererAPI.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"

#define GE_GetRenderAPI() ge::clientcore::RendererAPI::getAPI()
namespace ge {
	namespace clientcore {
		class Renderer {
		public:
			static void init();

			/// <summary>
			/// Begins a new scene
			/// </summary>
			static void beginScene(OrthographicCamera& camera);
			/// <summary>
			/// Ends the current scene
			/// </summary>
			static void endScene();
			
			/// <summary>
			/// Submits data to the scene
			/// </summary>
			/// <param name="arr">The vertex array to submit</param>
			static void submit(const ge::core::Ref<IShader>& shader, const ge::core::Ref<IVertexArray>& arr, const glm::mat4& transform = glm::mat4(1));

			static void onWindowResize(uint32 width, uint32 height);

			inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
		private:
			struct SceneData {
				glm::mat4 viewProjectionMatrix;
			};

			static SceneData* sceneData;
		};
	}
}
