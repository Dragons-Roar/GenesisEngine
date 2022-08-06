#include "RenderCommand.hpp"
#include "../platform/opengl/OpenGLRendererAPI.hpp"

namespace ge {
	namespace clientcore {
		RendererAPI* RenderCommand::api = new OpenGLRendererAPI();
	}
}
