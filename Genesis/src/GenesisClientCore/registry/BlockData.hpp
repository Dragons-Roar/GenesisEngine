#pragma once
#include "GenesisClientCore/Defines.hpp"
#include <GenesisCore/registry/BlockData.hpp>

namespace ge {
	namespace clientcore {
		/**
		 * @brief This class is used to store custom block data, used to be registered in the client-side registry
		 */
		class BlockData: public ge::core::BlockData {
		public:
			BlockData(glm::vec4 color): color(color) {
			}

			glm::vec4 color;

		private:
		};
	}
}
