#include "Shader.hpp"
#include "Renderer.hpp"

#include "../platform/opengl/OpenGLShader.hpp"

namespace ge {
	namespace clientcore {
		ge::core::Ref<IShader> IShader::create(const String& vertexFile, const String& fragmentFile) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLShader>(vertexFile, fragmentFile);
			}
			return nullptr;
		}
	}
}
