#pragma once
#include <GenesisCore/Layer.hpp>
#include <GenesisClientCore/Genesis.hpp>

namespace sb {
	class Sandbox2D: public ge::core::Layer {
	public:
		Sandbox2D():
			Layer("Sandbox2D"),
			camera(1280.f / 720.f) {
		}

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onImGUIRender() override;
		void onEvent(ge::core::Event& e) override;

	private:
		ge::clientcore::OrthographicCameraController camera;
		glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };

		ge::core::Ref<ge::clientcore::Texture2D> checkerboardTexture;
		ge::core::Ref<ge::clientcore::Texture2D> glowTexture;
	};
}
