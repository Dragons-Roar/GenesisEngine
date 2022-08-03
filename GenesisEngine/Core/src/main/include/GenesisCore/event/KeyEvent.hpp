#pragma once
#include "./Event.hpp"

namespace ge {
	namespace core {
		class KeyEvent: public Event {
		public:
			inline int32 getKeyCode() const { return keyCode; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyEvent{keyCode:" << keyCode << "}";
				return ss.str();
			}

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
		protected:
			KeyEvent(int32 keyCode): keyCode(keyCode) { }
			int32 keyCode;
		};

		class KeyDownEvent: public KeyEvent {
		public:
			KeyDownEvent(int32 keyCode, uint32 repeatCount): KeyEvent(keyCode), repeatCount(repeatCount) { }

			inline uint32 getRepeatCount() { return repeatCount; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyDownEvent{" << this->KeyEvent::toString() << ",keyCode:" << keyCode << " }";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyDown)

		private:
			uint32 repeatCount;
		};
		class KeyUpEvent: public KeyEvent {
		public:
			KeyUpEvent(int32 keyCode): KeyEvent(keyCode) { }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyUpEvent{" << this->KeyEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyUp)
		};
	}
}
