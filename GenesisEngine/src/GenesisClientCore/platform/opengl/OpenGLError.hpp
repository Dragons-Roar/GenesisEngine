#pragma once
#include "../../Defines.hpp"

#include <glad/glad.h>
#include <iostream>

void openGLDebugCallback(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void _GLGetError(const char* file, int line, const char* call);

#ifdef CM_Debug
#define glCheck(call) call; _GLGetError(__FILE__, __LINE__, #call)
#else
#define glCheck(call) call
#endif
