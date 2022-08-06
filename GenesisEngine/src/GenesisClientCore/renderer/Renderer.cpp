#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace ge {
	namespace clientcore {
		void Renderer::beginScene() {
		}
		void Renderer::endScene() {
		}

		void Renderer::submit(const IVertexArray* arr) {
			RenderCommand::drawIndexed(arr);
		}
	}
}
