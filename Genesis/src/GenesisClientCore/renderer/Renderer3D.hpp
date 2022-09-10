#pragma once
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace clientcore {

		/**
		 * @brief Pure static renderer class for rendering 3d scenes
		 */
		class Renderer3D {
		public:
			Renderer3D() = delete;

			static void init();
			static void shutdown();

			static void endScene();
		};
	}
}
