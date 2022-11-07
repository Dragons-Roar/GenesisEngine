#include "SandboxTestLayer.hpp"
#include <vector>

namespace sb {
	void SandboxTestLayer::onAttach() {
		std::vector<int32> ints;
		ints.reserve(4);

		ints.push_back(2);
		ints.push_back(4);
		ints.push_back(6);
		ints.push_back(8);

		std::vector<int32> ints2 = std::vector(ints);

		ints.clear();
		ints.push_back(10);

		ints.reserve(2);
	}
	void SandboxTestLayer::onDetach() {
	}
	void SandboxTestLayer::onUpdate(ge::core::Timestep ts) {
	}
	void SandboxTestLayer::onEvent(ge::core::Event& e) {
	}
	void SandboxTestLayer::onImGUIRender() {
	}
}
