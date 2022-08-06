#pragma once
#include "../../Defines.hpp"
#include "../../renderer/VertexArray.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLVertexArray: public IVertexArray {
		public:
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();

			void bind() const override;
			void unbind() const override;

			void addVertexBuffer(IVertexBuffer* buffer) override;
			void setIndexBuffer(IIndexBuffer* buffer) override;
			IIndexBuffer* getIndexBuffer() const override;

		private:
			uint32 handle;
			ge::core::List<IVertexBuffer*> vertexBuffers;
			IIndexBuffer* indexBuffer;
		};
	}
}
