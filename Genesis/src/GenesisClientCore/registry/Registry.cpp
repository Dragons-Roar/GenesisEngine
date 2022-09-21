#include "GenesisClientCore/registry/Registry.hpp"
#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace clientcore {
		Voxel Registry::currentVoxelID = 0;
		Registry::BlockList Registry::blockList = Registry::BlockList();
		Registry::BlockMap Registry::blockMap = Registry::BlockMap();

		void Registry::init() {
			registerBlock("air", BlockData(glm::vec4(0.f, 0.f, 0.f, 0.f)));
		}

		void Registry::registerBlock(const String& key, const BlockData& data) {
			Registry::Block* block = new Registry::Block(key, currentVoxelID, data);
			blockList.push_back(block);
			blockMap[key] = block;

			currentVoxelID++;
		}

		void Registry::printRegisteredBlocks() {
			GE_Info("--- {} Blocks registered! ---", currentVoxelID);
			for(Voxel i = 0; i < currentVoxelID; ++i) {
				GE_Info("{}: {}", i, getBlockByID(i).getKey());
			}
		}
	}
}
