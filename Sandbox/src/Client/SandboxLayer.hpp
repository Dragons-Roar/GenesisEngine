#pragma once
#include <GenesisClientCore/Genesis.hpp>
#include <glm/glm.hpp>

namespace sb {
	class SandboxLayer: public ge::core::Layer {
	public:
		SandboxLayer(): 
			ge::core::Layer("Sandbox Layer"),
			camera(-1.6f, 1.6f, -0.9f, 0.9f)
		{ }

		void onAttach() override;
		void onDetach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onImGUIRender() override;

	private:
		ge::clientcore::OrthographicCamera camera;

		ge::core::Ref<ge::clientcore::IShader> shader;
		ge::core::Ref<ge::clientcore::IVertexBuffer> vertexBuffer;
		ge::core::Ref<ge::clientcore::IIndexBuffer> indexBuffer;
		ge::core::Ref<ge::clientcore::IVertexArray> vertexArray;
	};
}
