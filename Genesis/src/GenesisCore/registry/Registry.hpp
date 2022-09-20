#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/registry/BlockData.hpp"

namespace ge {
	namespace core {
		class Registry {
		public:
			class Block {
			public:
				Block() = delete;
				String getKey() const { return key; }
				Voxel getID() const { return id; }
				const BlockData& getData() const { return data; }
			
			private:
				Block(String key, Voxel id, const BlockData& data): key(key), id(id), data(data) { }

				String key;
				Voxel id;
				BlockData data;
				
				friend class Registry;
			};

			using BlockList = std::vector<Registry::Block*>;
			using BlockMap = std::unordered_map<String, Registry::Block*>;

			static void init();

			static void registerBlock(const String& key, const BlockData& data);
			static Block& getBlockByID(Voxel id) { return *blockList[id]; }
			static Block& getBlockByKey(const String& key) { return *blockMap[key]; }

			static void printRegisteredBlocks();

		private:
			static Voxel currentVoxelID;
			static BlockList blockList;
			static BlockMap blockMap;
		};
	}
}
