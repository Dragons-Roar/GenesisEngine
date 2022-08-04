#pragma once
#include "../../Defines.hpp"
#include "../../GraphicsContext.hpp"

struct GLFWwindow;

namespace ge {
	namespace clientcore {
		class OpenGLContext: public ge::clientcore::IGraphicsContext {
		public:
			OpenGLContext(GLFWwindow* window);
			void init() override;
			void swapBuffers() override;
		private:
			GLFWwindow* window;
		};
	}
}
