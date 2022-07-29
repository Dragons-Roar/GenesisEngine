#include <GenesisCore/Serializer.hpp>

namespace ge {
	namespace core {
		void Serializer::init() {
			toml::table table = toml::parse_file("./config.toml");
			std::cout << "Port: " << table["Server"]["port"].value<uint32>().value() << std::endl;
		}
	}
}
