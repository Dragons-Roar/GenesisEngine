#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/Buffer.hpp"

namespace ge {
	namespace clientcore {
		class IVertexArray {
		public:
			virtual ~IVertexArray() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual void addVertexBuffer(ge::core::Ref<IVertexBuffer>& buffer) = 0;
			virtual void setIndexBuffer(ge::core::Ref<IIndexBuffer>& buffer) = 0;
			virtual ge::core::Ref<IIndexBuffer> getIndexBuffer() const = 0;

			static ge::core::Ref<IVertexArray> create();
		};
	}
}
