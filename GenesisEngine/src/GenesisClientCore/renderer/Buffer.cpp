#include "Buffer.hpp"
#include "Renderer.hpp"
#include <GenesisCore/Logger.hpp>

#include "../platform/opengl/OpenGLBuffer.hpp"

namespace ge {
	namespace clientcore {
		ge::core::Ref<IVertexBuffer> IVertexBuffer::create(float32* vertices, size_t size) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLVertexBuffer>(vertices, size);
			}
			return nullptr;
		}

		ge::core::Ref<IIndexBuffer> IIndexBuffer::create(uint32* indices, uint32 count) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLIndexBuffer>(indices, count);
			}
			return nullptr;
		}
	}
}
