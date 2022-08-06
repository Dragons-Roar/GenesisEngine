#include "Shader.hpp"
#include <GenesisCore/Logger.hpp>
#include "Renderer.hpp"

#include "../platform/opengl/OpenGLShader.hpp"

namespace ge {
	namespace clientcore {
		IShader* IShader::create(const String& vertexFile, const String& fragmentFile) {
			switch(Renderer::getAPI()) {
				case RendererAPI::None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case RendererAPI::OpenGL:	return new OpenGLShader(vertexFile, fragmentFile);
			}
		}
	}
}
