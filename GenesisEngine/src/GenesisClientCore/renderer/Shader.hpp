#pragma once
#include "../Defines.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		class Shader {
		public:
			Shader(const String& vertexShaderFile, const String& fragmentShaderFile);
			virtual ~Shader();

			void bind();
			void unbind();

			bool setUniform1f(const String& uniform, float32 x);
			bool setUniform2f(const String& uniform, float32 x, float32 y);
			bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z);
			bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a);
			bool setUniform1i(const String& uniform, int32 x);
			bool setUniform2i(const String& uniform, int32 x, int32 y);
			bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z);
			bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a);
			bool setUniform1b(const String& uniform, bool x);
			bool setUniformMatrix4fv(const String& uniform, const float32* data);

			GLuint getShaderID() {
				return shaderID;
			}
		private:
			uint32 compile(const String& shaderSrc, GLenum type);
			std::string parse(const String& file);
			uint32 createShader(const String& vertexShaderFile, const String& fragmentShaderFile);

			uint32 shaderID;

			#ifdef GE_DEBUG
			std::string d_vertexFile;
			std::string d_fragmentFile;
			#endif
		};
	}
}
