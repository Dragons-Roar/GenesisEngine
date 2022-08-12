#pragma once

#include "../../renderer/Texture.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLTexture2D: public Texture2D {
		public:
			OpenGLTexture2D(const String& path);
			~OpenGLTexture2D();

			uint32 getWidth() const { return width; }
			uint32 getHeight() const { return height; }

			void bind(uint32 slot) const override;

		private:
			String path;
			uint32 width, height;
			uint32 handle;
		};
	}
}
