#pragma once
#include "RendererAPI.hpp"

namespace ge {
	namespace clientcore {
		class RenderCommand {
		public:
			inline static void drawIndexed(const ge::core::Ref<IVertexArray>& arr) { api->drawIndexed(arr); }
			inline static void setClearColor(const glm::vec4& color) { api->setClearColor(color); }
			inline static void clear() { api->clear(); }

		private:
			static RendererAPI* api;
		};
	}
}
