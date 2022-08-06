#include "OpenGLRendererAPI.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}
		void OpenGLRendererAPI::clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::drawIndexed(const IVertexArray* arr) {
			arr->bind();
			glDrawElements(GL_TRIANGLES, arr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
