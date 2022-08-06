#pragma once
#include "../Defines.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		class IShader {
		public:
			static IShader* create(const String& vertexFile, const String& fragmentFile);

		public:
			virtual ~IShader() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual bool setUniform1f(const String& uniform, float32 x) = 0;
			virtual bool setUniform2f(const String& uniform, float32 x, float32 y) = 0;
			virtual bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z) = 0;
			virtual bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) = 0;
			virtual bool setUniform1i(const String& uniform, int32 x) = 0;
			virtual bool setUniform2i(const String& uniform, int32 x, int32 y) = 0;
			virtual bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z) = 0;
			virtual bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) = 0;
			virtual bool setUniform1b(const String& uniform, bool x) = 0;
			virtual bool setUniformMatrix4fv(const String& uniform, const float32* data) = 0;
		private:
		};
	}
}
