#include "OpenGLRendererAPI.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		void OpenGLRendererAPI::init() {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}

		void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}
		void OpenGLRendererAPI::clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::drawIndexed(const ge::core::Ref<IVertexArray>& arr, uint32 indexCount) {
			arr->bind();
			glDrawElements(GL_TRIANGLES, indexCount ? indexCount : arr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}

		void OpenGLRendererAPI::setViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
			glViewport(x, y, width, height);
		}

		void OpenGLRendererAPI::setWireframeMode(bool enable) {
			if(enable) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	}
}
