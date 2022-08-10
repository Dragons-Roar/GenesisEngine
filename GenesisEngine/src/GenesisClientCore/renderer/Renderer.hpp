#pragma once
#include "RendererAPI.hpp"
#include "RenderCommand.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#define GE_GetRenderAPI() ge::clientcore::RendererAPI::getAPI()
namespace ge {
	namespace clientcore {
		class Renderer {
		public:
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
			static void submit(const IShader* shader, const IVertexArray* arr, const glm::mat4& transform = glm::mat4(1));

			inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
		private:
			struct SceneData {
				glm::mat4 viewProjectionMatrix;
			};

			static SceneData* sceneData;
		};
	}
}
