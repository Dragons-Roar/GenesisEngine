#pragma once
#include "../Defines.hpp"
#include "./Buffer.hpp"

namespace ge {
	namespace clientcore {
		class IVertexArray {
		public:
			virtual ~IVertexArray() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual void addVertexBuffer(IVertexBuffer* buffer) = 0;
			virtual void setIndexBuffer(IIndexBuffer* buffer) = 0;
			virtual IIndexBuffer* getIndexBuffer() const = 0;

			static IVertexArray* create();
		};
	}
}
