#include <GenesisClientCore/platform/opengl/OpenGLContext.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace clientcore {
		OpenGLContext::OpenGLContext(GLFWwindow* window): window(window) {
			if(window == nullptr) std::cerr << "Window cannot be null!" << std::endl;
		}

		void OpenGLContext::init() {
			glfwMakeContextCurrent(window);
			int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
			if(!status) {
				GE_Fatal("Failed to initialize glad!");
			}

			GE_Info("OpenGL Info");
			GE_Info("  Vendor: {0}", glGetString(GL_VENDOR));
			GE_Info("  Renderer: {0}", glGetString(GL_RENDERER));
			GE_Info("  Version: {0}", glGetString(GL_VERSION));

			if(GLVersion.major < 4 || (GLVersion.major != 4 && GLVersion.minor < 5)) {
				GE_Fatal("Genesis Engine atleast needs OpenGL 4.5!");
			}

			glClearColor(0.f, 0.f, 0.f, 1.f);
		}
		void OpenGLContext::swapBuffers() {
			glfwSwapBuffers(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}
