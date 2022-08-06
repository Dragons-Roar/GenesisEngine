#pragma once
#include "../../Defines.hpp"
#include "../../renderer/Shader.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLShader: public IShader {
		public:
			OpenGLShader(const String& vertexFile, const String& fragmentFile);
			~OpenGLShader();

			virtual void bind() const override;
			virtual void unbind() const override;

			virtual bool setUniform1f(const String& uniform, float32 x) override;
			virtual bool setUniform2f(const String& uniform, float32 x, float32 y) override;
			virtual bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z) override;
			virtual bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) override;
			virtual bool setUniform1i(const String& uniform, int32 x) override;
			virtual bool setUniform2i(const String& uniform, int32 x, int32 y) override;
			virtual bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z) override;
			virtual bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) override;
			virtual bool setUniform1b(const String& uniform, bool x) override;
			virtual bool setUniformMatrix4fv(const String& uniform, const float32* data) override;

		private:
			uint32 compile(const String& shaderSrc, uint32 type);
			std::string parse(const String& file);
			uint32 createShader(const String& vertexShaderFile, const String& fragmentShaderFile);

			uint32 shaderID;

			#ifdef GE_DEBUG
			String d_vertexFile;
			String d_fragmentFile;
			#endif
		};
	}
}
