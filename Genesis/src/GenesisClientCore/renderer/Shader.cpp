#include "Shader.hpp"
#include "Renderer.hpp"

#include "../platform/opengl/OpenGLShader.hpp"

namespace ge {
	namespace clientcore {
		ge::core::Ref<IShader> IShader::create(const String& vertexSrc, const String& fragmentSrc) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
			}
			return nullptr;
		}
		ge::core::Ref<IShader> IShader::create(const String& file) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLShader>(file);
			}
			return nullptr;
		}
	}
}
