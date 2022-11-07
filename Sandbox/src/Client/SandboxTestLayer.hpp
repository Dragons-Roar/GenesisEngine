#pragma once
#include <GenesisCore/Layer.hpp>

namespace sb {
	class SandboxTestLayer: public ge::core::Layer {
	public:
		SandboxTestLayer(): ge::core::Layer("SandboxTestLayer") {
		}

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onEvent(ge::core::Event& e) override;
		void onImGUIRender() override;
	};
}
