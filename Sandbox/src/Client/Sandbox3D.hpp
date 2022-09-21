#pragma once
#include <GenesisClientCore/Genesis.hpp>
#include <GenesisCore/world/World.hpp>
#include "GenesisClientCore/WorldGenerator.hpp"

namespace sb {
	class Sandbox3D: public ge::core::Layer {
	public:
		Sandbox3D(): Layer("Sandbox3D"), world("world", new ge::clientcore::WorldGenerator()), camera(1920.f / 1080.f, 90.f) {
		}

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onImGUIRender() override;
		void onEvent(ge::core::Event& e) override;

	private:
		bool onKeyDown(ge::core::KeyDownEvent& e);

		ge::clientcore::PerspectiveCameraController camera;
		ge::core::World world;
	};
}
