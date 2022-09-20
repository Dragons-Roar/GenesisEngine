#pragma once
#include <GenesisClientCore/Genesis.hpp>

namespace sb {
	class Sandbox3D: public ge::core::Layer {
	public:
		Sandbox3D(): Layer("Sandbox3D"), camera(1920.f / 1080.f, 90.f) {
		}

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onImGUIRender() override;
		void onEvent(ge::core::Event& e) override;

	private:
		ge::clientcore::PerspectiveCameraController camera;
	};
}
