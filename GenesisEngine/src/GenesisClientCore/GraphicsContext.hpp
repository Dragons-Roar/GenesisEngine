#pragma once
#include <GenesisCore/GenesisBase.hpp>

namespace ge {
	namespace clientcore {
		class IGraphicsContext: public ge::core::GClass {
		public:
			IGraphicsContext() = default;
			virtual ~IGraphicsContext() = default;

			virtual void init() = 0;
			virtual void swapBuffers() = 0;

			static IGraphicsContext* create(void* window);
		};
	}
}
