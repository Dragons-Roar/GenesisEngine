#pragma once
#include <GenesisCore/Layer.hpp>
#include <GenesisCore/event/Event.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <GenesisCore/event/MouseEvent.hpp>
#include <GenesisCore/event/WindowEvent.hpp>

namespace ge {
	namespace clientcore {
		class ImGUILayer: public ge::core::Layer {
		public:
			ImGUILayer(): ge::core::Layer("ImGUI Layer") {}

			void onAttach() override;
			void onDetach() override;
			void onUpdate() override;
			void onEvent(ge::core::Event& e) override;

		private:
			bool onMouseButtonDownEvent(ge::core::MouseButtonDownEvent& e);
			bool onMouseButtonUpEvent(ge::core::MouseButtonUpEvent& e);
			bool onMouseMovedEvent(ge::core::MouseMovedEvent& e);
			bool onMouseScrolledEvent(ge::core::MouseScrolledEvent& e);
			bool onKeyDownEvent(ge::core::KeyDownEvent& e);
			bool onKeyUpEvent(ge::core::KeyUpEvent& e);
			bool onKeyTypedEvent(ge::core::KeyTypedEvent& e);
			bool onWindowResizeEvent(ge::core::WindowResizeEvent& e);
		};
	}
}
