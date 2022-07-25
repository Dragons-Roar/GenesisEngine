#include <GenesisClient/GenesisClient.hpp>
#include <GenesisCore/List.hpp>
#include <GenesisCore/Version.hpp>
#include <GenesisCore/String.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;
	ge::client::GenesisClient::init();

	ge::core::List<uint32> list;
	ge::core::String str = "20,71,65,72";
	str.splitNum(list);

	list.sort([](const uint32& a, const uint32& b) {
		return a > b;
	});

	ge::core::Version v(1, 8, 7, 69);
	ge::core::String vString = v.format();
	ge::core::String iString = "Test";

	std::cout << "ILength: " << iString.length() << std::endl;
	std::cout << vString << std::endl;
	std::cout << "Length: " << vString.length() << std::endl;
	vString.insert(5, "Test");
	std::cout << "Length: " << vString.length() << std::endl;
	vString.insert(5, iString);
	std::cout << vString << " Length: " << vString.length() << std::endl;
	vString.replace("Test", "KeinTest");
	std::cout << vString << " Length: " << vString.length() << std::endl;

	ge::core::String numString = "Ergebnis: ";
	std::cout << numString << " Length: " << numString.length() << std::endl;
}
