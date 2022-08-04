#pragma once
#include "../../Defines.hpp"
#include <GLFW/glfw3.h>
#include "../../Window.hpp"
#include "../opengl/OpenGLContext.hpp"

namespace ge {
	namespace clientcore {
		struct WindowData: public ge::core::GClass {
		public:
			const String toString() const override {
				std::stringstream ss;
				ss << "ge::clientcore::WindowData{title:" << title << ",width:" << width << ",height:" << height << ",vSync:" << vSync << "}";
				return ss.str();
			}

			String title;
			uint32 width, height;
			bool vSync;
			IWindow::EventCallback eventFunc;
		};

		class WindowsWindow: public IWindow {
		public:
			static IWindow* create(const WindowProps& props = WindowProps());

			WindowsWindow(const WindowProps& props);
			~WindowsWindow();

			void init(const WindowProps& props);
			void shutdown();

			void onUpdate() override;
			inline uint32 getWidth() const override;
			inline uint32 getHeight() const override;
			inline float32 getWidthF() const override;
			inline float32 getHeightF() const override;

			void setEventCallback(const EventCallback& func) override;
			void setVSync(bool enable) override;
			bool isVSync() const override;

			bool shouldClose() const override {
				return glfwWindowShouldClose(handle);
			}

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::clientcore::WindowsWindow{data:" << data.toString() << ",#glfwWindowCount:" << glfwWindowCount << "}";
				return ss.str();
			}

		private:
			WindowData data;
			GLFWwindow* handle;
			OpenGLContext* context;

			static uint8 glfwWindowCount;
		};
	}
}
