#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/Genesis.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::Version v("1.87.689+89524");
	std::cout << v.getMajor() << " " << v.getMinor() << " " << v.getPatch() << " " << v.getBuild() << std::endl;
	std::cout << v.format() << std::endl;
	std::cout << v.toString() << std::endl;

	ge::core::List<uint32> list;
	list.add(327);
	list.add(192);
	list.add(237);
	list.add(2383);
	list.add(37);
	list.add(237);

	list.sort([](uint32 a, uint32 b) {
		return a < b;
	});

	std::cout << list.join(",") << std::endl;
	std::cout << list.toString() << std::endl;

	ge::core::Serializer::init();
}
