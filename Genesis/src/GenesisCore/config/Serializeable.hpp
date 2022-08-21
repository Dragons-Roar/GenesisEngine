#pragma once
#include "GenesisCore/config/Config.hpp"

namespace ge {
	namespace core {
		class Serializable {
		public:
			virtual void serialize(ConfigSection& section) const = 0;
			virtual void deserialize(ConfigSection& section) = 0;

			void saveToFile(const String& file) {
				ConfigSection sec;
				serialize(sec);
				ConfigFile::fromSection(file, sec).save();
			}
			void loadFromFile(const String& file) {
				ConfigFile cf(file);
				cf.load();
				auto sec = ge::core::ConfigSection(cf.getHandle());
				deserialize(sec);
			}
		};
	}
}
