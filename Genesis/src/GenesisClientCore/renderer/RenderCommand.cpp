#include "RenderCommand.hpp"
#include "GenesisClientCore/platform/opengl/OpenGLRendererAPI.hpp"

namespace ge {
	namespace clientcore {
		RendererAPI* RenderCommand::api = new OpenGLRendererAPI();
	}
}
