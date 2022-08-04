#include <GenesisClientCore/platform/opengl/OpenGLContext.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		OpenGLContext::OpenGLContext(GLFWwindow* window): window(window) {
			if(window == nullptr) std::cerr << "Window cannot be null!" << std::endl;
		}

		void OpenGLContext::init() {
			glfwMakeContextCurrent(window);
			int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
			if(!status) {
				std::cerr << "Failed to initialize glad!" << std::endl;
			}

			std::cout << "OpenGL Info:\n";
			std::cout << "  Version: " << GLVersion.major << "." << GLVersion.minor << "\n";
			std::cout << "  Vendor: " << glGetString(GL_VENDOR) << "\n";
			std::cout << "  Renderer: " << glGetString(GL_RENDERER) << "\n";
			std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

			if(GLVersion.major < 4 || (GLVersion.major != 4 && GLVersion.minor < 5)) {
				std::cerr << "Genesis Engine atleast needs OpenGL 4.5!" << std::endl;
			}
		}
		void OpenGLContext::swapBuffers() {
			glfwSwapBuffers(window);
		}
	}
}
