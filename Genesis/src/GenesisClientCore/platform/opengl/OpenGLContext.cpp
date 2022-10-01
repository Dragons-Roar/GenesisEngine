#include <GenesisClientCore/platform/opengl/OpenGLContext.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GenesisCore/Logger.hpp>
#include <GenesisCore/Config.hpp>

#include "GenesisClientCore/platform/opengl/OpenGLError.hpp"

namespace ge {
	namespace clientcore {
		OpenGLContext::OpenGLContext(GLFWwindow* window): window(window) {
			if(window == nullptr) std::cerr << "Window cannot be null!" << std::endl;
		}

		void OpenGLContext::init() {
			GE_ProfileFunction();

			// Set context and initialize glad
			glfwMakeContextCurrent(window);
			if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				GE_Fatal("Failed to initialize glad!");
			}

			// Print some opengl system info
			GE_Info("OpenGL Info");
			GE_Info("  Vendor: {0}", glGetString(GL_VENDOR));
			GE_Info("  Renderer: {0}", glGetString(GL_RENDERER));
			GE_Info("  Version: {0}", glGetString(GL_VERSION));

			if(GLVersion.major < 4 || (GLVersion.major != 4 && GLVersion.minor < 5)) {
				GE_Fatal("Genesis Engine atleast needs OpenGL 4.5!");
			}

			// Enable OpenGL Debug Callback
			#if GE_CONFIG_GL_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openGLDebugCallback, 0);
			#endif

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glEnable(GL_COLOR_MATERIAL);

			// Sets the clear color to a standard
			// Does not need to use RenderComand abstraction because
			// this code will only be ran if OpenGL is the selected
			// renderer api
			glClearColor(0.f, 0.f, 0.f, 1.f);
		}
		void OpenGLContext::swapBuffers() {
			glfwSwapBuffers(window);
		}
	}
}
