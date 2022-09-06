#include "Texture.hpp"
#include "GenesisClientCore/platform/opengl/OpenGLTexture.hpp"
#include "RendererAPI.hpp"


namespace ge {
	namespace clientcore {
		ge::core::Ref<Texture2D> Texture2D::create(const String& path) {
			switch(RendererAPI::getAPI()) {
				case RendererAPI::API::NONE: GE_Assert(false, "RendererAPI::None is currently not supported!");
				case RendererAPI::API::OPENGL: return ge::core::CreateRef<OpenGLTexture2D>(path);
			}
		}

		ge::core::Ref<Texture2D> Texture2D::create(uint32 width, uint32 height) {
			switch(RendererAPI::getAPI()) {
				case RendererAPI::API::NONE: GE_Assert(false, "RendererAPI::None is currently not supported!");
				case RendererAPI::API::OPENGL: return ge::core::CreateRef<OpenGLTexture2D>(width, height);
			}
		}
	}
}
