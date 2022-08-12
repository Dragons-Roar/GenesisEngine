#pragma once
#include <GenesisClientCore/Genesis.hpp>
#include <glm/glm.hpp>

namespace sb {
	class SandboxLayer: public ge::core::Layer {
	public:
		SandboxLayer(): 
			ge::core::Layer("Sandbox Layer"),
			camera(1280.f / 720.f)
		{ }

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onEvent(ge::core::Event& e) override;
		void onImGUIRender() override;

	private:
		ge::clientcore::OrthographicCameraController camera;

		ge::core::Ref<ge::clientcore::IVertexBuffer> vertexBuffer;
		ge::core::Ref<ge::clientcore::IIndexBuffer> indexBuffer;
		ge::core::Ref<ge::clientcore::IVertexArray> vertexArray;
		ge::core::Ref<ge::clientcore::Texture2D> texture;
		ge::core::Ref<ge::clientcore::Texture2D> glow;

		ge::clientcore::ShaderLibrary shaderLibrary;
	};
}
