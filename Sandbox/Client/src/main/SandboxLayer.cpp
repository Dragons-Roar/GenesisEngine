#include "SandboxLayer.hpp"
#include <GenesisClientCore/Genesis.hpp>

#include <imgui.h>

namespace sb {
	void SandboxLayer::onAttach() {
		GE_Info("Sandbox Layer has been attached!");
		vertexArray = ge::clientcore::IVertexArray::create();
		vertexArray->unbind();

		float32 vertices[3 * 7] = {
			-0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f,
			 0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f, 1.f,
			 0.f,   0.5f, 0.f, 0.f, 0.f, 1.f, 1.f
		};

		ge::clientcore::BufferLayout layout = {
			{ ge::clientcore::ShaderDataType::FLOAT3, "a_pos" },
			{ ge::clientcore::ShaderDataType::FLOAT4, "a_color" }
		};

		uint32 index = 0;
		vertexBuffer = ge::clientcore::IVertexBuffer::create(vertices, sizeof(vertices));
		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);

		uint32 indices[3] = { 0, 1, 2 };
		indexBuffer = ge::clientcore::IIndexBuffer::create(indices, 3);
		vertexArray->setIndexBuffer(indexBuffer);

		shader = ge::clientcore::IShader::create("assets/shader/basic.vert", "assets/shader/basic.frag");
	}
	void SandboxLayer::onDetach() {
		GE_Info("Sandbox Layer has been detached!");
		delete indexBuffer;
		delete vertexBuffer;
		delete vertexArray;
		delete shader;
	}
	void SandboxLayer::onUpdate() {
		if(ge::clientcore::Input::isKeyDown(ge::Key::W)) {
			camera.setPosition(camera.getPosition() + glm::vec3(0.f, 0.1f, 0.f));
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::S)) {
			camera.setPosition(camera.getPosition() + glm::vec3(0.f, -0.1f, 0.f));
		}

		if(ge::clientcore::Input::isKeyDown(ge::Key::A)) {
			camera.setPosition(camera.getPosition() + glm::vec3(-0.1f, 0.f, 0.f));
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::D)) {
			camera.setPosition(camera.getPosition() + glm::vec3(0.1f, 0.f, 0.f));
		}

		if(ge::clientcore::Input::isKeyDown(ge::Key::Q)) {
			camera.setRotation(camera.getRotation() + 1.f);
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::E)) {
			camera.setRotation(camera.getRotation() - 1.f);
		}

		ge::clientcore::RenderCommand::clear();

		ge::clientcore::Renderer::beginScene(camera);
		ge::clientcore::Renderer::submit(shader, vertexArray);
		ge::clientcore::Renderer::endScene();
	}
	void SandboxLayer::onImGUIRender() {
		bool open = true;
		ImGui::Begin("Camera Info", &open);
		ImGui::Text("Position:");
		ImGui::Text(String("X: " + std::to_string(camera.getPosition().x) + " Y: " + std::to_string(camera.getPosition().y) + " Z: " + std::to_string(camera.getPosition().z)).c_str());
		ImGui::Text("Rotation:");
		ImGui::Text(String("Z: " + std::to_string(camera.getRotation())).c_str());
		ImGui::End();
	}
}
