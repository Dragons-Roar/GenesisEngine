#include "Shader.hpp"
#include "Renderer.hpp"

#include "../platform/opengl/OpenGLShader.hpp"

namespace ge {
	namespace clientcore {
		ge::core::Ref<IShader> IShader::create(const String& name, const String& vertexSrc, const String& fragmentSrc) {
			switch(GE_GetRenderAPI()) {
				case GE_RendererAPI_None:		GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RendererAPI_OpenGL:		return ge::core::CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
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

		void ShaderLibrary::add(const String& name, const ge::core::Ref<IShader>& shader) {
			GE_Assert(!exists(name), "Shader already exists!");
			shaders[name] = shader;
		}
		void ShaderLibrary::add(const ge::core::Ref<IShader>& shader) {
			auto& name = shader->getName();
			add(name, shader);
		}
		
		ge::core::Ref<IShader> ShaderLibrary::load(const String& file) {
			auto shader = IShader::create(file);
			add(shader);
			return shader;
		}
		ge::core::Ref<IShader> ShaderLibrary::load(const String& name, const String& file) {
			auto shader = IShader::create(file);
			add(name, shader);
			return shader;
		}
		ge::core::Ref<IShader> ShaderLibrary::get(const String& name) {
			GE_Assert(exists(name), "Shader not found!");
			return shaders[name];
		}
	}
}
