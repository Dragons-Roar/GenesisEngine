#include "Sandbox3D.hpp"
#include <imgui.h>
#include <GenesisCore/world/World.hpp>
#include <GenesisCore/world/ChunkColumn.hpp>
#include <GenesisCore/world/Chunk.hpp>
#include <GenesisCore/registry/Registry.hpp>
#include <GenesisClientCore/renderer/WorldRenderer.hpp>
#include <glad/glad.h>

namespace sb {
	void Sandbox3D::onAttach() {
		GE_ProfileFunction();

		ge::clientcore::Application::getInstance().getWindow().setCursorGrabbed(true);

		ge::core::ChunkColumn* column = world.getColumn(ChunkPos(0, 0));
		column->chunks[0]->setVoxel(10, 0, 0, 0);

		ge::core::Registry::printRegisteredBlocks();
	}
	void Sandbox3D::onDetach() {
		GE_ProfileFunction();
	}
	void Sandbox3D::onUpdate(ge::core::Timestep ts) {
		GE_ProfileFunction();

		camera.onUpdate(ts);

		ge::clientcore::RenderCommand::clear();

		ge::clientcore::WorldRenderer::beginScene(camera.getCamera());
		ge::clientcore::WorldRenderer::renderColumn(world.getColumn(ChunkPos(0, 0)));
		ge::clientcore::WorldRenderer::endScene();
	}
	void Sandbox3D::onImGUIRender() {
		GE_ProfileFunction();

		ImGui::Begin("Camera Stats");
		ImGui::Text("X: %f, Y: %f, Z: %f", camera.getCamera().getPos().x, camera.getCamera().getPos().y, camera.getCamera().getPos().z);
		ImGui::Text("Yaw: %f, Pitch: %f", camera.getCamera().getYaw(), camera.getCamera().getPitch());
		ImGui::Text("Voxel: %i", world.getColumn(ChunkPos(0, 0))->chunks[0]->getVoxel(0, 0, 0));
		ImGui::End();
	}
	void Sandbox3D::onEvent(ge::core::Event& e) {
		GE_ProfileFunction();

		camera.onEvent(e);
	}
}
