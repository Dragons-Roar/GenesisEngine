#include "Sandbox3D.hpp"
#include <imgui.h>
#include <GenesisCore/world/World.hpp>

namespace sb {
	void Sandbox3D::onAttach() {
		GE_ProfileFunction();

		ge::clientcore::Application::getInstance().getWindow().setCursorGrabbed(true);

		ge::core::World world("world");
		ge::core::ChunkColumn* column = world.getColumn(ChunkPos(0, 0));
		ge::core::ChunkColumn* column2 = world.getColumn(ChunkPos(0, 1));
		ge::core::ChunkColumn* column3 = world.getColumn(ChunkPos(1, 0));
		ge::core::ChunkColumn* column4 = world.getColumn(ChunkPos(0, 0));
	}
	void Sandbox3D::onDetach() {
		GE_ProfileFunction();
	}
	void Sandbox3D::onUpdate(ge::core::Timestep ts) {
		GE_ProfileFunction();

		camera.onUpdate(ts);

		ge::clientcore::RenderCommand::clear();
		ge::clientcore::Renderer3D::beginScene(camera.getCamera());
		ge::clientcore::Renderer3D::drawCube(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
		ge::clientcore::Renderer3D::endScene();
	}
	void Sandbox3D::onImGUIRender() {
		GE_ProfileFunction();

		ImGui::Begin("Camera Stats");
		ImGui::Text("X: %f, Y: %f, Z: %f", camera.getCamera().getPos().x, camera.getCamera().getPos().y, camera.getCamera().getPos().z);
		ImGui::Text("Yaw: %f, Pitch: %f", camera.getCamera().getYaw(), camera.getCamera().getPitch());
		ImGui::End();
	}
	void Sandbox3D::onEvent(ge::core::Event& e) {
		GE_ProfileFunction();

		camera.onEvent(e);
	}
}
