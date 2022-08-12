#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/RendererAPI.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLRendererAPI: public RendererAPI {
		public:
			void init() override;

			void setClearColor(const glm::vec4& color) override;
			void clear() override;

			void setViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;

			void drawIndexed(const ge::core::Ref<IVertexArray>& arr) override;
		};
	}
}
