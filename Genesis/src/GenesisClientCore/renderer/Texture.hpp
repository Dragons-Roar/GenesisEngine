#pragma once
#include "GenesisClientCore/Defines.hpp"

namespace ge {
	namespace clientcore {
		class Texture {
		public:
			virtual ~Texture() {}

			virtual uint32 getWidth() const = 0;
			virtual uint32 getHeight() const = 0;
			virtual void bind(uint32 slot = 0) const = 0;
		};

		class Texture2D: public Texture {
		public:
			static ge::core::Ref<Texture2D> create(const String& path);
		};
	}
}
