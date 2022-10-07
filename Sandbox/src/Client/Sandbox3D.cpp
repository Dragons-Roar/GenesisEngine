#include "Sandbox3D.hpp"
#include <imgui.h>
#include <GenesisCore/world/World.hpp>
#include <GenesisCore/world/ChunkColumn.hpp>
#include <GenesisCore/world/Chunk.hpp>
#include <GenesisClientCore/registry/Registry.hpp>
#include <GenesisClientCore/renderer/WorldRenderer.hpp>
#include <GenesisCore/KeyCode.hpp>
#include <glad/glad.h>

namespace sb {
	void Sandbox3D::onAttach() {
		GE_ProfileFunction();

		ge::clientcore::Application::getInstance().getWindow().setCursorGrabbed(true);

		ge::clientcore::Registry::init();
		ge::clientcore::Registry::registerBlock("red", ge::clientcore::BlockData(glm::vec4(1.f, 0.f, 0.f, 1.f)));
		ge::clientcore::Registry::registerBlock("green", ge::clientcore::BlockData(glm::vec4(0.f, 1.f, 0.f, 1.f)));
		ge::clientcore::Registry::registerBlock("blue", ge::clientcore::BlockData(glm::vec4(0.f, 0.f, 1.f, 1.f)));
		ge::clientcore::Registry::registerBlock("magenta", ge::clientcore::BlockData(glm::vec4(1.f, 0.f, 1.f, 1.f)));
		ge::clientcore::Registry::printRegisteredBlocks();

		ge::core::ChunkColumn* column = world.getColumn(ChunkPos(0, 0));
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("red").getID(), 0, 0, 0);
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("green").getID(), 1, 0, 0);
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("green").getID(), 1, 1, 0);
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("blue").getID(), 2, 0, 0);
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("blue").getID(), 2, 1, 0);
		column->chunks[0]->setVoxel(ge::clientcore::Registry::getBlockByKey("blue").getID(), 2, 2, 0);

		ge::clientcore::WorldRenderer::beginWorld(&world);
	}
	void Sandbox3D::onDetach() {
		GE_ProfileFunction();
	}
	void Sandbox3D::onUpdate(ge::core::Timestep ts) {
		GE_ProfileFunction();

		ge::clientcore::WorldRenderer::clearStats();

		camera.onUpdate(ts);

		ge::clientcore::RenderCommand::clear();
		ge::clientcore::WorldRenderer::beginScene(camera.getCamera());
		ge::clientcore::WorldRenderer::updateChunks();
		ge::clientcore::WorldRenderer::drawChunks();
	}
	void Sandbox3D::onImGUIRender() {
		GE_ProfileFunction();

		ge::core::Location loc = camera.getCamera().getLocation();
		auto chunk = loc.getChunkPos();
		auto worldStats = ge::clientcore::WorldRenderer::getStats();

		ImGui::Begin("Camera Stats");
		ImGui::Text("X/Y/Z %i / %i / %i (%f / %f / %f)", (int) loc.getX(), (int) loc.getY(), (int) loc.getZ(), loc.getXr(), loc.getYr(), loc.getZr());
		ImGui::Text("CX/CZ %i / %i", chunk.x, chunk.y);
		ImGui::Text("Yaw/Pitch: %f / %f", camera.getCamera().getYaw(), camera.getCamera().getPitch());
		ImGui::Text("Chunks: %i (%i)", (int) worldStats->chunkCount, (int) (worldStats->chunkCount * GE_WORLD_HEIGHT));
		ImGui::End();
	}
	void Sandbox3D::onEvent(ge::core::Event& e) {
		GE_ProfileFunction();

		ge::core::EventDispatcher dispatcher(e);
		dispatcher.dispatch<ge::core::KeyDownEvent>(GE_BindEventFunction(Sandbox3D::onKeyDown));

		camera.onEvent(e);
	}

	bool Sandbox3D::onKeyDown(ge::core::KeyDownEvent& e) {
		if(e.getKeyCode() == ge::Key::F) {
			world.setVoxel(ge::clientcore::Registry::getBlockByKey("magenta").getID(), 0, 0, 0);
		}

		if(e.getKeyCode() == ge::Key::G) {
			ge::core::ChunkColumn* column = world.getColumn(ChunkPos(0, 1));

			for(uint8 x = 0; x < GE_CHUNK_SIZE; ++x) {
				for(uint8 z = 0; z < GE_CHUNK_SIZE; ++z) {
					for(uint16 i = 0; i < 20; ++i) {
						column->setVoxel(ge::clientcore::Registry::getBlockByKey("magenta").getID(), x, i, z);
					}
				}
			}
			column->setDirty(false);
		}
		if(e.getKeyCode() == ge::Key::H) {
			ge::core::ChunkColumn* column = world.getColumn(ChunkPos(0, 1));
			column->setDirty(true);
		}

		return false;
	}
}
