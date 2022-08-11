#include "OpenGLVertexArray.hpp"
#include <glad/glad.h>

namespace ge {
	namespace clientcore {
		static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
			switch(type) {
				case ShaderDataType::FLOAT:		return GL_FLOAT;
				case ShaderDataType::FLOAT2:	return GL_FLOAT;
				case ShaderDataType::FLOAT3:	return GL_FLOAT;
				case ShaderDataType::FLOAT4:	return GL_FLOAT;
				case ShaderDataType::INT:		return GL_INT;
				case ShaderDataType::INT2:		return GL_INT;
				case ShaderDataType::INT3:		return GL_INT;
				case ShaderDataType::INT4:		return GL_INT;
				case ShaderDataType::MAT3:		return GL_FLOAT;
				case ShaderDataType::MAT4:		return GL_FLOAT;
				case ShaderDataType::BOOL:		return GL_BOOL;
			}
			GE_Assert(false, "Unknown shader data type!");
			return 0;
		}

		OpenGLVertexArray::OpenGLVertexArray() {
			glGenVertexArrays(1, &handle);
			glBindVertexArray(handle);
		}
		OpenGLVertexArray::~OpenGLVertexArray() {
		}

		void OpenGLVertexArray::bind() const {
			glBindVertexArray(handle);
		}
		void OpenGLVertexArray::unbind() const {
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::addVertexBuffer(ge::core::Ref<IVertexBuffer>& buffer) {
			GE_Assert(buffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");
			glBindVertexArray(handle);
			buffer->bind();

			auto layout = buffer->getLayout();

			uint32 i = 0;
			for(const auto& element : layout) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i,
					element.getComponentCount(),
					shaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*) element.offset);
				i++;
			}

			vertexBuffers.add(buffer);
		}
		void OpenGLVertexArray::setIndexBuffer(ge::core::Ref<IIndexBuffer>& buffer) {
			glBindVertexArray(handle);
			buffer->bind();

			indexBuffer = buffer;
		}
		ge::core::Ref<IIndexBuffer> OpenGLVertexArray::getIndexBuffer() const {
			return indexBuffer;
		}
	}
}
