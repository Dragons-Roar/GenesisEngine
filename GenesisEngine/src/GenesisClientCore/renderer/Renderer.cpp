#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace ge {
	namespace clientcore {
		Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData();

		void Renderer::beginScene(OrthographicCamera& camera) {
			sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
		}
		void Renderer::endScene() {
		}

		void Renderer::submit(const IShader* shader, const IVertexArray* arr) {
			shader->bind();
			shader->setUniformMatrix4fv("u_viewProjectionMatrix", sceneData->viewProjectionMatrix);
			RenderCommand::drawIndexed(arr);
		}
	}
}
