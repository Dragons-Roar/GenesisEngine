#pragma once
#include "../Defines.hpp"
#include <glm/glm.hpp>

namespace ge {
	namespace clientcore {
		class IShader {
		public:
			static ge::core::Ref<IShader> create(const String& vertexSrc, const String& fragmentSrc);
			static ge::core::Ref<IShader> create(const String& file);

		public:
			virtual ~IShader() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual bool setUniform1f(const String& uniform, float32 x) const = 0;
			virtual bool setUniform2f(const String& uniform, float32 x, float32 y) const = 0;
			virtual bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z) const = 0;
			virtual bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) const = 0;
			virtual bool setUniform1i(const String& uniform, int32 x) const = 0;
			virtual bool setUniform2i(const String& uniform, int32 x, int32 y) const = 0;
			virtual bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z) const = 0;
			virtual bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) const = 0;
			virtual bool setUniform1b(const String& uniform, bool x) const = 0;
			virtual bool setUniformMatrix4fv(const String& uniform, const glm::mat4& data) const = 0;
		private:
		};
	}
}
