#include <GenesisClientCore/GraphicsContext.hpp>

#ifdef GE_OPENGL
#	include <GenesisClientCore/platform/opengl/OpenGLContext.hpp>
#	include <GLFW/glfw3.h>
#else
#	error Undefined RenderingAPI! Currently only OpenGL is supported!
#endif

namespace ge {
	namespace clientcore {
		IGraphicsContext* IGraphicsContext::create(void* window) {
			#ifdef GE_OPENGL
			return new ge::clientcore::OpenGLContext((GLFWwindow*) window);
			#endif
			return nullptr;
		}
	}
}
