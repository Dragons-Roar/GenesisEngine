#include "Sandbox2D.hpp"
#include <GenesisClientCore/renderer/Renderer.hpp>
#include <GenesisClientCore/renderer/Renderer2D.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

namespace sb {
	void Sandbox2D::onAttach() {
		GE_ProfileFunction();

		checkerboardTexture = ge::clientcore::Texture2D::create("assets/textures/checkerboard.png");
		glowTexture = ge::clientcore::Texture2D::create("assets/textures/glow.png");
	}
	void Sandbox2D::onDetach() {
	}

	void Sandbox2D::onUpdate(ge::core::Timestep ts) {
		GE_ProfileFunction();

		camera.onUpdate(ts);

		ge::clientcore::RenderCommand::clear();
		ge::clientcore::Renderer2D::beginScene(camera.getCamera());
		ge::clientcore::Renderer2D::drawQuad({0.f, 0.f}, {1.2f, 0.7f}, color);
		ge::clientcore::Renderer2D::drawQuad({0.f, 0.f}, {0.1f, 0.3f}, color);
		ge::clientcore::Renderer2D::drawQuadRotated({10.f, 10.f}, {3.f, 3.f}, checkerboardTexture, glm::radians(color.w * 100.f), color, {10.f, 10.f});
		ge::clientcore::Renderer2D::endScene();
	}
	void Sandbox2D::onImGUIRender() {
		GE_ProfileFunction();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
		ImGui::End();
	}

	void Sandbox2D::onEvent(ge::core::Event& e) {
		GE_ProfileFunction();

		camera.onEvent(e);
	}
}
