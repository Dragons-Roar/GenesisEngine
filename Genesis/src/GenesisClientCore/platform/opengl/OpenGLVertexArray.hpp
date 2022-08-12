#pragma once
#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLVertexArray: public IVertexArray {
		public:
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();

			void bind() const override;
			void unbind() const override;

			void addVertexBuffer(ge::core::Ref<IVertexBuffer>& buffer) override;
			void setIndexBuffer(ge::core::Ref<IIndexBuffer>& buffer) override;
			ge::core::Ref<IIndexBuffer> getIndexBuffer() const override;

		private:
			uint32 handle;
			ge::core::List<ge::core::Ref<IVertexBuffer>> vertexBuffers;
			ge::core::Ref<IIndexBuffer> indexBuffer;
		};
	}
}
