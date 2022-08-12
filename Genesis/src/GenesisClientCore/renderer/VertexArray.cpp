#include "VertexArray.hpp"
#include "Renderer.hpp"

#include "GenesisClientCore/platform/opengl/OpenGLVertexArray.hpp"

namespace ge {
	namespace clientcore {
		ge::core::Ref<IVertexArray> IVertexArray::create() {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLVertexArray>();
			}
			return nullptr;
		}
	}
}
