#pragma once
#include "GenesisCore/event/Event.hpp"

namespace ge {
	namespace core {
		class MouseMovedEvent: public Event {
		public:
			MouseMovedEvent(float32 x, float32 y): x(x), y(y) { }

			/// <summary>
			/// Gets the absolute xpos
			/// </summary>
			/// <returns>The xpos</returns>
			inline float32 getX() { return x; }
			/// <summary>
			/// Gets the absolute ypos
			/// </summary>
			/// <returns>The ypos</returns>y
			inline float32 getY() { return y; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseMovedEvent{x:" << x << "y:" << y << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
				EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float32 x, y;
		};

		class MouseScrolledEvent: public Event {
		public:
			MouseScrolledEvent(float32 x, float32 y): x(x), y(y) { }

			inline float32 getX() { return x; }
			inline float32 getY() { return y; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseScrolledEvent{x:" << x << "y:" << y << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseScrolled)
				EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float32 x, y;
		};

		class MouseButtonEvent: public Event {
		public:
			MouseButtonEvent(uint8 btn): btn(btn) { }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseButtonEvent{button:" << btn << "}";
				return ss.str();
			}

			inline uint32 getButton() { return btn; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		private:
			uint32 btn;
		};

		class MouseButtonDownEvent: public MouseButtonEvent {
		public:
			MouseButtonDownEvent(uint8 btn): MouseButtonEvent(btn) { }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseButtonDownEvent{" << this->MouseButtonEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonDown)
		};
		class MouseButtonUpEvent: public MouseButtonEvent {
		public:
			MouseButtonUpEvent(uint8 btn): MouseButtonEvent(btn) { }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseButtonUpEvent{" << this->MouseButtonEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonUp)
		};
	}
}
