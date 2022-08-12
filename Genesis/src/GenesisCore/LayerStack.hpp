#pragma once
#include "GenesisCore/Layer.hpp"

namespace ge {
	namespace core {
		class LayerStack {
		public:
			LayerStack() = default;
			~LayerStack();

			/// <summary>
			/// Push a new layer onto the stack
			/// </summary>
			/// <param name="layer">The layer to push</param>
			void pushLayer(Layer* layer);
			/// <summary>
			/// Push a new overlay onto the stack (overlays will always be at the top)
			/// </summary>
			/// <param name="layer">The overlay to push</param>
			void pushOverlay(Layer* layer);
			/// <summary>
			/// Remove a layer from the stack
			/// </summary>
			/// <param name="layer">The layer</param>
			void popLayer(Layer* layer);
			/// <summary>
			/// Remove a overlay from the stack
			/// </summary>
			/// <param name="layer">The overlay</param>
			void popOverlay(Layer* layer);

			inline std::vector<Layer*>::iterator begin() { return layers.begin(); }
			inline std::vector<Layer*>::iterator end() { return layers.end(); }
			inline std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
			inline std::vector<Layer*>::reverse_iterator rend() { return layers.rend(); }

			inline std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
			inline std::vector<Layer*>::const_iterator end()	const { return layers.end(); }
			inline std::vector<Layer*>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
			inline std::vector<Layer*>::const_reverse_iterator rend() const { return layers.rend(); }
		private:
			std::vector<Layer*> layers;
			uint32 layerInsertIndex = 0;
		};
	}
}
