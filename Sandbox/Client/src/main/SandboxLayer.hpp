#pragma once
#include <GenesisClientCore/Genesis.hpp>

namespace sb {
	class SandboxLayer: public ge::core::Layer {
	public:
		SandboxLayer(): 
			ge::core::Layer("Sandbox Layer"),
			camera(-1.6f, 1.6f, -0.9f, 0.9f)
		{ }

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onImGUIRender() override;

	private:
		ge::clientcore::OrthographicCamera camera;

		ge::clientcore::IShader* shader;
		ge::clientcore::IVertexBuffer* vertexBuffer;
		ge::clientcore::IIndexBuffer* indexBuffer;
		ge::clientcore::IVertexArray* vertexArray;
	};
}
