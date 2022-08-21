#pragma once
#include <GenesisClientCore/Genesis.hpp>
#include <GenesisCore/Layer.hpp>
#include <GenesisCore/config/Serializeable.hpp>

namespace sb {
	// A simple class to demonstrate de/serializing
	class TestPlayer: public ge::core::Serializable {
	public:
		TestPlayer() {}

		void serialize(ge::core::ConfigSection& section) const override {
			section.set<String>("name", name);
			section.set<int32>("x", x);
			section.set<int32>("y", y);
			section.set<int32>("z", z);
		}
		void deserialize(ge::core::ConfigSection& section) override {
			name = section.getDefault<String>("name", "Player");
			x = section.getDefault<int32>("x", 0);
			y = section.getDefault<int32>("y", 0);
			z = section.getDefault<int32>("z", 0);
		}

		String name;
		int32 x, y, z;
	};

	class Sandbox2D: public ge::core::Layer {
	public:
		Sandbox2D(): Layer("Sandbox2D"),
		             camera(1280.f / 720.f) {
		}

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onImGUIRender() override;
		void onEvent(ge::core::Event& e) override;

	private:
		ge::clientcore::OrthographicCameraController camera;
		glm::vec4 color = {1.f, 1.f, 1.f, 1.f};

		ge::core::Ref<ge::clientcore::Texture2D> checkerboardTexture;
		ge::core::Ref<ge::clientcore::Texture2D> glowTexture;
	};
}
