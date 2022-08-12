#pragma once
#include "GenesisCore/KeyCode.hpp"
#include "GenesisCore/event/Event.hpp"

namespace ge {
	namespace core {
		class KeyEvent: public Event {
		public:
			inline KeyCode getKeyCode() const { return keyCode; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyEvent{keyCode:" << keyCode << "}";
				return ss.str();
			}

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
		protected:
			KeyEvent(KeyCode keyCode): keyCode(keyCode) { }
			KeyCode keyCode;
		};

		class KeyDownEvent: public KeyEvent {
		public:
			KeyDownEvent(KeyCode keyCode, uint32 repeatCount): KeyEvent(keyCode), repeatCount(repeatCount) { }

			inline uint32 getRepeatCount() { return repeatCount; }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyDownEvent{" << this->KeyEvent::toString() << ",repeatCount:" << repeatCount << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyDown)

		private:
			uint32 repeatCount;
		};
		class KeyUpEvent: public KeyEvent {
		public:
			KeyUpEvent(KeyCode keyCode): KeyEvent(keyCode) { }

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyUpEvent{" << this->KeyEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyUp)
		};

		class KeyTypedEvent: public KeyEvent {
		public:
			KeyTypedEvent(const KeyCode keycode)
				: KeyEvent(keycode) {}

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::KeyTypedEvent{" << this->KeyEvent::toString() << "}";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}
