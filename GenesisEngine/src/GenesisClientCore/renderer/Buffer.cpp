#include "Buffer.hpp"
#include "Renderer.hpp"
#include <GenesisCore/Logger.hpp>

#include "../platform/opengl/OpenGLBuffer.hpp"

namespace ge {
	namespace clientcore {
		IVertexBuffer* IVertexBuffer::create(float32* vertices, size_t size) {
			switch(Renderer::getAPI()) {
				case RendererAPI::None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
			}
		}

		IIndexBuffer* IIndexBuffer::create(uint32* indices, uint32 count) {
			switch(Renderer::getAPI()) {
				case RendererAPI::None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, count);
			}
		}
	}
}
