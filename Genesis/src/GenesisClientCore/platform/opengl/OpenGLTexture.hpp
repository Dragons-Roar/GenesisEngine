#pragma once

#include "GenesisClientCore/renderer/Texture.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		class OpenGLTexture2D: public Texture2D {
		public:
			OpenGLTexture2D(const String& path);
			OpenGLTexture2D(uint32 width, uint32 height);
			~OpenGLTexture2D();

			uint32 getWidth() const { return width; }
			uint32 getHeight() const { return height; }

			void bind(uint32 slot) const override;
			void setData(void* data, uint32 size) override;

			bool OpenGLTexture2D::operator==(const Texture& other) const override {
				return handle == ((OpenGLTexture2D&) other).handle;
			}
			bool OpenGLTexture2D::operator!=(const Texture& other) const override {
				return handle != ((OpenGLTexture2D&) other).handle;
			}

		private:
			String path;
			uint32 width, height;
			uint32 handle;

			GLenum internalFormat, dataFormat;
		};
	}
}
