#pragma once
#include "../Defines.hpp"

namespace ge {
	namespace clientcore {
		class IVertexBuffer {
		public:
			virtual ~IVertexBuffer() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			static IVertexBuffer* create(float32* vertices, size_t size);
		};
		
		class IIndexBuffer {
		public:
			virtual ~IIndexBuffer() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual uint32 getCount() const = 0;

			static IIndexBuffer* create(uint32* indices, uint32 count);
		};
	}
}
