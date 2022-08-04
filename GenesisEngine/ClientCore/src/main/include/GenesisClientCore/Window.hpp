#pragma once
#include "./Defines.hpp"
#include <GenesisCore/event/Event.hpp>

namespace ge {
	namespace clientcore {
		struct WindowProps {
			String title;
			uint32 width, height;

			WindowProps(const String& title = "Genesis Engine",
				uint32 width = 1280, uint32 height = 720): title(title), width(width), height(height) {
			}
		};
		
		class IWindow {
		public:
			typedef std::function<void(ge::core::Event&)> EventCallback;

			static IWindow* create(const WindowProps& props = WindowProps());
			virtual ~IWindow() {}

			virtual void onUpdate() = 0;
			virtual uint32 getWidth() const = 0;
			virtual uint32 getHeight() const = 0;
			virtual float32 getWidthF() const = 0;
			virtual float32 getHeightF() const = 0;

			// Temporary!!! Will later be handled using WindowCloseEvent!
			virtual inline bool shouldClose() const = 0;

			virtual void setEventCallback(const EventCallback& func) = 0;
			virtual void setVSync(bool enable) = 0;
			virtual bool isVSync() const = 0;

		protected:

		private:
		};
	}
}
