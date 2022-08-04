#pragma once
#include "../../Defines.hpp"
#include <GLFW/glfw3.h>
#include "../../Window.hpp"

namespace ge {
	namespace clientcore {
		struct WindowData {
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

		private:
			WindowData data;
			GLFWwindow* handle;

			static uint8 glfwWindowCount;
		};
	}
}
