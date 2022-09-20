#include "Renderer3D.hpp"
#include "GenesisClientCore/renderer/Buffer.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Renderer.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisCore/Logger.hpp"

namespace ge {
	namespace clientcore {
		Renderer3D::Data* Renderer3D::data = nullptr;

		void Renderer3D::init() {
			GE_ProfileFunction();

			GE_Info("Initializing Renderer3D...");
			data = new Renderer3D::Data();
			data->shader = IShader::create("assets/shader/3d/basic.glsl");
		}
		void Renderer3D::shutdown() {
			GE_ProfileFunction();

			GE_Info("Shutting down Renderer3D...");
			delete data;
		}

		void Renderer3D::beginScene(const PerspectiveCamera& camera) {
			GE_ProfileFunction();

			data->shader->bind();
			glm::mat4 mat(1.f);
			data->shader->setUniformMatrix4fv("u_viewProjectionMatrix", camera.getViewProjectionMatrix());
			//data->shader->setUniform1i("u_texture", 0);
		}

		void Renderer3D::drawCube(const glm::vec3& from, const glm::vec3& to, const glm::vec4& color) {
			GE_ProfileFunction();

			float32 vertices[20] = {
				-0.5f, -0.5f, 0.f, 0.f, 0.f,
				 0.5f, -0.5f, 0.f, 1.f, 0.f,
				 0.5f,  0.5f, 0.f, 1.f, 1.f,
				-0.5f,  0.5f, 0.f, 0.f, 1.f
			};

			uint32 indices[6] = {
				0, 1, 2,
				2, 3, 0
			};

			ge::core::Ref<IVertexArray> array = IVertexArray::create();
			ge::core::Ref<IVertexBuffer> vertex = IVertexBuffer::create(vertices, sizeof(float32) * 20);
			ge::core::Ref<IIndexBuffer> index = IIndexBuffer::create(indices, 6);

			vertex->setLayout({
				{ ShaderDataType::FLOAT3, "a_pos" },
				{ ShaderDataType::FLOAT2, "a_uv" }
			});

			array->addVertexBuffer(vertex);
			array->setIndexBuffer(index);

			RenderCommand::drawIndexed(array, index->getCount());
		}

		void Renderer3D::endScene() {
			GE_ProfileFunction();
		}
	}
}
