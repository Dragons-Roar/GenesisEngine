#pragma once
#include "../../Input.hpp"

namespace ge {
	namespace clientcore {
		class WindowsInput: public Input {
		protected:
			virtual bool isKeyDownImpl(KeyCode keycode) override;
			virtual bool isMouseDownImpl(int32 keycode) override;
			virtual float32 getMouseXImpl() override;
			virtual float32 getMouseYImpl() override;
			virtual std::pair<float32, float32> getMousePosImpl() override;
		};
	}
}
