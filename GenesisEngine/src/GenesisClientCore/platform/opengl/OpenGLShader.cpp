#include "OpenGLShader.hpp"
#include <GenesisCore/Logger.hpp>

#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		OpenGLShader::OpenGLShader(const String& vertexFile, const String& fragmentFile) {
			shaderID = createShader(vertexFile, fragmentFile);

			#ifdef GE_DEBUG
			this->d_vertexFile = vertexFile;
			this->d_fragmentFile = fragmentFile;
			#endif
		}
		OpenGLShader::~OpenGLShader() {
			glDeleteProgram(shaderID);
		}

		void OpenGLShader::bind() const {
			glUseProgram(shaderID);
		}
		void OpenGLShader::unbind() const {
			glUseProgram(0);
		}

		GLuint OpenGLShader::compile(const std::string& shaderSrc, GLenum type) {
			GLuint shaderID = glCreateShader(type);
			const char* src = shaderSrc.c_str();
			glShaderSource(shaderID, 1, &src, 0);
			glCompileShader(shaderID);

			int32 result;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
			if(result != GL_TRUE) {
				int32 length = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				char* msg = new char[length];
				glGetShaderInfoLog(shaderID, length, &length, msg);
				GE_Error("OpenGLShader compilation error: {0}", msg);
				delete[] msg;
				return 0;
			}
			return shaderID;
		}
		std::string OpenGLShader::parse(const String& fileName) {
			FILE* file;
			file = fopen(fileName.c_str(), "rb");
			if(file == nullptr) {
				GE_Info("File {0} not found!", fileName);
				return "";
			}

			std::string contents;
			fseek(file, 0, SEEK_END);
			size_t fileSize = ftell(file);
			rewind(file);
			contents.resize(fileSize);

			fread(&contents[0], 1, fileSize, file);
			fclose(file);

			return contents;
		}
		GLuint OpenGLShader::createShader(const String& vertexFile, const String& fragmentFile) {
			std::string vertexOpenGLShaderSRC = parse(vertexFile);
			std::string fragmentOpenGLShaderSRC = parse(fragmentFile);

			GLuint programID = glCreateProgram();
			GE_Info("Compiling {0}...", vertexFile);
			GLuint vertexShaderID = compile(vertexOpenGLShaderSRC, GL_VERTEX_SHADER);
			GE_Info("Compiling {0}...", fragmentFile);
			GLuint fragmentShaderID = compile(fragmentOpenGLShaderSRC, GL_FRAGMENT_SHADER);

			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			uint32 isLinked = 0;
			glGetProgramiv(programID, GL_LINK_STATUS, (int*) &isLinked);
			if(isLinked == GL_FALSE) {
				int32 maxLength = 0;
				glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<char> infoLog(maxLength);
				glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

				glDeleteProgram(programID);
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);

				GE_Error("OpenGLShader link error: {0}", infoLog.data());

				return 0;
			}

			#ifndef GE_DEBUG
			glDetachOpenGLShader(programID, vertexShaderID);
			glDetachOpenGLShader(programID, fragmentShaderID);

			glDeleteOpenGLShader(vertexShaderID);
			glDeleteOpenGLShader(fragmentShaderID);
			#endif

			return programID;
		}

		bool OpenGLShader::setUniform1f(const String& uniform, float32 x) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform1f(location, x);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform1f(location, x);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform2f(const String& uniform, float32 x, float32 y) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform2f(location, x, y);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform2f(location, x, y);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform3f(const String& uniform, float32 x, float32 y, float32 z) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform3f(location, x, y, z);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform3f(location, x, y, z);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform4f(location, x, y, z, a);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform4f(location, x, y, z, a);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform1i(const String& uniform, int32 x) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform1i(location, x);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform1i(location, x);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform2i(const String& uniform, int32 x, int32 y) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform2i(location, x, y);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform2i(location, x, y);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform3i(const String& uniform, int32 x, int32 y, int32 z) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform3i(location, x, y, z);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform3i(location, x, y, z);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniform4i(location, x, y, z, a);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniform4i(location, x, y, z, a);
			return true;
			#endif
		}
		bool OpenGLShader::setUniform1b(const String& uniform, bool x) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				if(x) {
					glUniform1i(location, 1);
				} else {
					glUniform1i(location, 0);
				}

				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			if(x) {
				glUniform1i(location, 1);
			} else {
				glUniform1i(location, 0);
			}
			return true;
			#endif
		}

		bool OpenGLShader::setUniformMatrix4fv(const String& uniform, const float32* data) {
			int32 location = glGetUniformLocation(shaderID, uniform.c_str());

			#ifdef GE_DEBUG
			if(location != -1) {
				glUniformMatrix4fv(location, 1, GL_FALSE, data);
				return true;
			} else {
				GE_Warn("{0} not found! Vertex: {1} Fragment: {2}", uniform, d_vertexFile, d_fragmentFile);
				return false;
			}
			#else
			glUniformMatrix4fv(location, 1, GL_FALSE, data);
			return true;
			#endif
		}
	}
}
