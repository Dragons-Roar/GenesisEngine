#include "Renderer.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Renderer2D.hpp"

namespace ge {
	namespace clientcore {
		Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData();

		void Renderer::init() {
			RenderCommand::init();
			Renderer2D::init();
		}

		void Renderer::beginScene(OrthographicCamera& camera) {
			GE_ProfileFunction();

			sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
		}
		void Renderer::endScene() {
		}

		void Renderer::submit(const ge::core::Ref<IShader>& shader, const ge::core::Ref<IVertexArray>& arr, const glm::mat4& transform) {
			GE_ProfileFunction();

			shader->bind();
			shader->setUniformMatrix4fv("u_viewProjectionMatrix", sceneData->viewProjectionMatrix);
			shader->setUniformMatrix4fv("u_transformMatrix", transform);

			RenderCommand::drawIndexed(arr);
		}

		void Renderer::onWindowResize(uint32 width, uint32 height) {
			RenderCommand::setViewport(0, 0, width, height);
		}
	}
}
