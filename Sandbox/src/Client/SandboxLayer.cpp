#include "SandboxLayer.hpp"
#include <GenesisClientCore/Genesis.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

namespace sb {
	void SandboxLayer::onAttach() {
		GE_Info("Sandbox Layer has been attached!");
		vertexArray = ge::clientcore::IVertexArray::create();
		vertexArray->unbind();

		float32 vertices[4 * 5] = {
			-0.5f, -0.5f, 0.f, 0.f, 0.f,
			 0.5f, -0.5f, 0.f, 1.f, 0.f,
			 0.5f,  0.5f, 0.f, 1.f, 1.f,
			-0.5f,  0.5f, 0.f, 0.f, 1.f
		};

		ge::clientcore::BufferLayout layout = {
			{ ge::clientcore::ShaderDataType::FLOAT3, "a_pos" },
			{ ge::clientcore::ShaderDataType::FLOAT2, "a_uv" }
		};

		uint32 index = 0;
		vertexBuffer = ge::clientcore::IVertexBuffer::create(vertices, sizeof(vertices));
		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);

		uint32 indices[6] = {
			0, 1, 2, 
			2, 3, 0
		};
		indexBuffer = ge::clientcore::IIndexBuffer::create(indices, 6);
		vertexArray->setIndexBuffer(indexBuffer);

		auto shader = shaderLibrary.load("assets/shader/basic.glsl");
		shader->bind();
		shader->setUniform1i("u_texture", 0);

		texture = ge::clientcore::Texture2D::create("assets/textures/checkerboard.png");
		glow = ge::clientcore::Texture2D::create("assets/textures/glow.png");
	}
	void SandboxLayer::onDetach() {
		GE_Info("Sandbox Layer has been detached!");
	}
	void SandboxLayer::onUpdate(ge::core::Timestep ts) {
		if(ge::clientcore::Input::isKeyDown(ge::Key::W)) {
			camera.setPosition(camera.getPosition() + glm::vec3(0.f, 3.f * ts, 0.f));
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::S)) {
			camera.setPosition(camera.getPosition() + glm::vec3(0.f, -3.f * ts, 0.f));
		}

		if(ge::clientcore::Input::isKeyDown(ge::Key::A)) {
			camera.setPosition(camera.getPosition() + glm::vec3(-3.f * ts, 0.f, 0.f));
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::D)) {
			camera.setPosition(camera.getPosition() + glm::vec3(3.f * ts, 0.f, 0.f));
		}

		if(ge::clientcore::Input::isKeyDown(ge::Key::Q)) {
			camera.setRotation(camera.getRotation() + 80.f * ts);
		} else if(ge::clientcore::Input::isKeyDown(ge::Key::E)) {
			camera.setRotation(camera.getRotation() - 80.f * ts);
		}

		ge::clientcore::RenderCommand::clear();

		ge::clientcore::Renderer::beginScene(camera);
		
		auto shader = shaderLibrary.get("basic");

		texture->bind();
		ge::clientcore::Renderer::submit(shader, vertexArray);
		glow->bind();
		ge::clientcore::Renderer::submit(shader, vertexArray);

		ge::clientcore::Renderer::endScene();
	}
	void SandboxLayer::onImGUIRender() {
		bool open = true;
		ImGui::Begin("Camera Info");
		ImGui::Text("Position:");
		ImGui::Text(String("X: " + std::to_string(camera.getPosition().x) + " Y: " + std::to_string(camera.getPosition().y) + " Z: " + std::to_string(camera.getPosition().z)).c_str());
		ImGui::Text("Rotation:");
		ImGui::Text(String("Z: " + std::to_string(camera.getRotation())).c_str());
		ImGui::End();
	}
}
