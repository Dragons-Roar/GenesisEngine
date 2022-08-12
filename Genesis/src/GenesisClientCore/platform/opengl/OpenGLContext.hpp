#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/GraphicsContext.hpp"

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
