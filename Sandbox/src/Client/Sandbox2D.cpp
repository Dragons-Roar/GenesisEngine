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

		ge::clientcore::Renderer2D::resetStats();

		camera.onUpdate(ts);

		ge::clientcore::RenderCommand::clear();

		ge::clientcore::Renderer2D::beginScene(camera.getCamera());
		for(uint32 a = 0; a < 255; ++a) {
			for(uint32 b = 0; b < 255; ++b) {
				float32 fa = 1.f / 255.f * a;
				float32 fb = 1.f / 255.f * b;

				ge::clientcore::Renderer2D::drawQuad({a * 0.25f, b * 0.25f}, {0.2f, 0.2f}, {0.f, fa, fb, 1.f});
			}
		}
		ge::clientcore::Renderer2D::endScene();
	}
	void Sandbox2D::onImGUIRender() {
		GE_ProfileFunction();

		auto stats = ge::clientcore::Renderer2D::getStats();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("DrawCalls: %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getVertexCount());
		ImGui::Text("Indices: %d", stats.getIndicesCount());
		ImGui::End();
	}

	void Sandbox2D::onEvent(ge::core::Event& e) {
		GE_ProfileFunction();

		camera.onEvent(e);
	}
}
