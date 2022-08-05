#pragma once

namespace ge {
	namespace clientcore {
		// DirectX will later be added
		enum class RendererAPI {
			None = 0,
			OpenGL = 1
		};

		class Renderer {
		public:
			inline static RendererAPI getAPI() { return rendererAPI; }
		private:
			static RendererAPI rendererAPI;
		};
	}
}
