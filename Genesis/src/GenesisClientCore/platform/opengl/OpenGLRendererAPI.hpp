#pragma once
#include "../../Defines.hpp"
#include "../../renderer/RendererAPI.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLRendererAPI: public RendererAPI {
		public:
			void init() override;

			void setClearColor(const glm::vec4& color) override;
			void clear() override;

			void drawIndexed(const ge::core::Ref<IVertexArray>& arr) override;
		};
	}
}
