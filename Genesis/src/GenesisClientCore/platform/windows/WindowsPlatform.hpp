#pragma once
#include "../../Platform.hpp"

namespace ge {
	namespace clientcore {
		class WindowsPlatform: public Platform {
		public:
			float32 getTimeImpl() const override;
		};
	}
}
