#include "OpenGLError.hpp"
#include <GenesisCore/Logger.hpp>

void __stdcall openGLDebugCallback(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	GE_Info("OpenGL: {0}", message);
}

void _GLGetError(const char* file, int line, const char* call) {
	while(GLenum error = glGetError()) {
		const unsigned char* str_error = glGetString(error);
		if(str_error == nullptr) {
			GE_Info("Unknown", std::string(file), line);
			return;
		}
		GE_Info("OpenGL Error ({1}:{2}): {0}", str_error, file, line);
	}
}
