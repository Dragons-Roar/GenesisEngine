#include "Sandbox2D.hpp"
#include <GenesisClientCore/renderer/Renderer.hpp>
#include <GenesisClientCore/renderer/Renderer2D.hpp>
#include <GenesisCore/Genesis.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/stacktrace.hpp>

#include <imgui.h>

#include "TestThread.hpp"

namespace sb {
	void Sandbox2D::onAttach() {
		GE_ProfileFunction();

		ge::core::CommandManager::runCommand("wireframe enable");

		ge::core::ConfigFile file("assets/test.json");
		file.load();

		GE_Info("Test: {0}", file.get<uint32>("Test"));
		GE_Info("Test2: {0}", file.get<int32>("Test2"));

		GE_Info("Port: {0}", file.getSection("server")->getDefault<uint32>("port", 20176));
		GE_Info("Player: {0}", file.getSection("player")->getDefault<String>("name", "Player"));

		file.keys(true, [](const String& key) {
			GE_Info("Key: {0}", key);
		});

		file.setColor("color", ge::core::Color(255, 0, 255, 255));
		ge::core::Color color = file.getColor("color");
		GE_Info("Color: {0}", color.format());
		GE_Info("{0} {1} {2} {3}", color.getR(), color.getG(), color.getB(), color.getA());

		ge::core::ConfigSection* playerSection = file.getSection("player2");

		TestPlayer player;
		player.deserialize(*playerSection);
		GE_Info("Name: {0}, X: {1}, Y: {2}, Z: {3}", player.name, player.x, player.y, player.z);
		player.serialize(*playerSection);

		file.save(true);

		checkerboardTexture = ge::clientcore::Texture2D::create("assets/textures/checkerboard.png");
		glowTexture = ge::clientcore::Texture2D::create("assets/textures/glow.png");

		TestThread* t = new TestThread();
		t->start();
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
