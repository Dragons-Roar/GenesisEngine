#include "OpenGLBuffer.hpp"
#include <glad/glad.h>
#include "OpenGLError.hpp"

namespace ge {
	namespace clientcore {
		OpenGLVertexBuffer::OpenGLVertexBuffer(float32* vertices, size_t size) {
			glCheck(glCreateBuffers(1, &handle));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, handle));
			glCheck(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
		}
		OpenGLVertexBuffer::~OpenGLVertexBuffer() {
			glDeleteBuffers(1, &handle);
		}

		void OpenGLVertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, handle);
		}
		void OpenGLVertexBuffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count): count(count) {
			glCheck(glCreateBuffers(1, &handle));
			glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
			glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW));
		}
		OpenGLIndexBuffer::~OpenGLIndexBuffer() {
			glDeleteBuffers(1, &handle);
		}

		uint32 OpenGLIndexBuffer::getCount() const {
			return count;
		}
		
		void OpenGLIndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		}
		void OpenGLIndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
