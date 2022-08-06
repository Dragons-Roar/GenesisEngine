#include "VertexArray.hpp"
#include "Renderer.hpp"

#include "../platform/opengl/OpenGLVertexArray.hpp"

namespace ge {
	namespace clientcore {
		IVertexArray* IVertexArray::create() {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return new OpenGLVertexArray();
			}
			return nullptr;
		}
	}
}
