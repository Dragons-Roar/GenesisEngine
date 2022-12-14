#pragma once
#include "GenesisCore/event/Event.hpp"
#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace core {
		class MouseMovedEvent: public Event {
		public:
			MouseMovedEvent(float32 x, float32 y) {
				this->x = x;
				this->y = y;
			}
			~MouseMovedEvent() {
				xLast = this->x;
				yLast = this->y;
			}

			/**
			 * @brief Gets the absolute x pos
			 * @return float32
			 */
			inline float32 getX() { return x; }
			/**
			 * @brief Gets the absolute y pos
			 * @return float32
			 */
			inline float32 getY() { return y; }

			/**
			 * @brief Gets the relative x pos since last update
			 * @return float32
			 */
			inline float32 getXRel() { return x - xLast; }
			/**
			 * @brief Gets the relative y pos since last update
			 * @return float32
			 */
			inline float32 getYRel() { return y - yLast; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseMovedEvent{x:" << x << "y:" << y << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float32 x, y;
			static float32 xLast, yLast;
		};

		class MouseScrolledEvent: public Event {
		public:
			MouseScrolledEvent(float32 x, float32 y): x(x), y(y) {}

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
			MouseButtonEvent(uint8 btn): btn(btn) {}

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
			MouseButtonDownEvent(uint8 btn): MouseButtonEvent(btn) {}

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseButtonDownEvent{" << this->MouseButtonEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonDown)
		};
		class MouseButtonUpEvent: public MouseButtonEvent {
		public:
			MouseButtonUpEvent(uint8 btn): MouseButtonEvent(btn) {}

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::MouseButtonUpEvent{" << this->MouseButtonEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonUp)
		};
	}
}
