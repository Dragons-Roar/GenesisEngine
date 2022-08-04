#include <GenesisClientCore/platform/windows/WindowsWindow.hpp>
#include <glad/glad.h>
#include <GenesisClientCore/GraphicsContext.hpp>

namespace ge {
	namespace clientcore {
		uint8 WindowsWindow::glfwWindowCount = 0;

		static void GLFWErrorCallback(int error, const char* description) {
			std::cout << "GLFW Error (" << error << "): " << description << std::endl;
		}

		WindowsWindow::WindowsWindow(const WindowProps& props) {
			init(props);
		}
		WindowsWindow::~WindowsWindow() {
			shutdown();
		}

		void WindowsWindow::init(const WindowProps& props) {
			// Set Window Props
			data.title = props.title;
			data.width = props.width;
			data.height = props.height;

			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_DECORATED, true);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
			glfwWindowHint(GLFW_ALPHA_BITS, 8);
			glfwWindowHint(GLFW_RED_BITS, 8);
			glfwWindowHint(GLFW_GREEN_BITS, 8);
			glfwWindowHint(GLFW_BLUE_BITS, 8);

			// Create Window
			std::cout << "Creating Window '" << props.title << "'" << std::endl;
			if(glfwWindowCount == 0) {
				// If first window, initialize GLFW
				std::cout << "Inititalizing GLFW..." << std::endl;
				int success = glfwInit();
				if(!success) {
					std::cerr << "Could not initialize GLFW!" << std::endl;
				}
				glfwSetErrorCallback(GLFWErrorCallback);
			}

			// If not in distribution, enable opengl debug logs
			#ifndef GE_DIST
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif

			// Now create the window and create the context
			// Context will later be abstracted to support also directx and vulkan context
			handle = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
			context = (ge::clientcore::OpenGLContext*) ge::clientcore::IGraphicsContext::create(handle);
			context->init();

			setVSync(true);
			glfwSetWindowUserPointer(handle, &data);

			++glfwWindowCount;

			// Set GLFW Callbacks
			glfwSetWindowSizeCallback(handle, [](GLFWwindow* window, int32 width, int32 height) {
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
				data.width = width; data.height = height;
			});
		}

		void WindowsWindow::onUpdate() {
			glfwPollEvents();
			context->swapBuffers();
		}
		uint32 WindowsWindow::getWidth() const { return data.width; }
		uint32 WindowsWindow::getHeight() const { return data.height; }

		float32 WindowsWindow::getWidthF() const { return (float32) data.width; }
		float32 WindowsWindow::getHeightF() const { return (float32) data.height; }

		void WindowsWindow::setEventCallback(const EventCallback& func) {
		}
		void WindowsWindow::setVSync(bool enable) {
			data.vSync = enable;
			glfwSwapInterval(data.vSync ? 1 : 0);
		}
		bool WindowsWindow::isVSync() const { return data.vSync; }

		void WindowsWindow::shutdown() {
			glfwWindowCount--;
			std::cout << "Destroying '" << data.title << "'..." << std::endl;
			glfwDestroyWindow(handle);
			--glfwWindowCount;

			if(glfwWindowCount == 0) glfwTerminate();
			
			delete context;
		}
	}
}
