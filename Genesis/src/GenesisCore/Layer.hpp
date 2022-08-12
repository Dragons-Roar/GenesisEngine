#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/event/Event.hpp"
#include "GenesisCore/Timestep.hpp"

namespace ge {
	namespace core {
		class Layer {
		public:
			Layer(const String& name = "Layer"): debugName(name) {}
			virtual ~Layer() = default;

			virtual void onAttach() {}
			virtual void onDetach() {}
			virtual void onUpdate(Timestep ts) {}
			virtual void onEvent(Event& e) {}
			virtual void onImGUIRender() {}

			const String& getName() const { return debugName; }
		private:
			String debugName;
		};
	}
}
