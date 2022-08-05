#pragma once
#include "../../renderer/Buffer.hpp"

namespace ge {
	namespace clientcore {
		class OpenGLVertexBuffer: public IVertexBuffer {
		public:
			OpenGLVertexBuffer(float32* vertices, size_t size);
			virtual ~OpenGLVertexBuffer();

			void bind() const override;
			void unbind() const override;

		private:
			uint32 handle;
		};

		class OpenGLIndexBuffer: public IIndexBuffer {
		public:
			OpenGLIndexBuffer(uint32* indices, uint32 count);
			virtual ~OpenGLIndexBuffer();

			uint32 getCount() const override;

			void bind() const override;
			void unbind() const override;

		private:
			uint32 handle;
			uint32 count;
		};
	}
}
