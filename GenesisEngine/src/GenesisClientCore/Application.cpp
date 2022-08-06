#include <GenesisClientCore/Application.hpp>
#include <GenesisClientCore/imgui/ImGUILayer.hpp>
#include <GenesisClientCore/Input.hpp>
#include <GenesisCore/Logger.hpp>

#include <GLFW/glfw3.h>

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

		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& config): appConfig(config) {
			if(instance) std::cerr << "Application already exists!" << std::endl;
			instance = this;

			window = IWindow::create(WindowProps(config.name));
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));

			imGuiLayer = new ImGUILayer();
			layerStack.pushOverlay(imGuiLayer);

			// ---> Temporary OpenGL Code <--- //
			glGenVertexArrays(1, &vertexArray);
			glBindVertexArray(vertexArray);

			float32 vertices[3 * 7] = {
				-0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f,
				 0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f, 1.f,
				 0.f,   0.5f, 0.f, 0.f, 0.f, 1.f, 1.f
			};

			BufferLayout layout = {
				{ ShaderDataType::FLOAT3, "a_pos" },
				{ ShaderDataType::FLOAT4, "a_color" }
			};


			uint32 index = 0;
			vertexBuffer = IVertexBuffer::create(vertices, sizeof(vertices));
			for(const auto& element : layout) {
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, 
					element.getComponentCount(),
					shaderDataTypeToOpenGLBaseType(element.type), 
					element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*) element.offset);

				index++;
			}

			uint32 indices[3] = { 0, 1, 2 };
			indexBuffer = IIndexBuffer::create(indices, 3);

			shader = IShader::create("assets/shader/basic.vert", "assets/shader/basic.frag");
		}
		Application::~Application() {
		}

		void Application::close() {
			running = false;
		}
		
		void Application::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);
			// Dispatch event directly to internal functions
			dispatcher.dispatch<ge::core::WindowCloseEvent>(GE_BindEventFunction(Application::onWindowClose));
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(Application::onWindowResize));

			// Go through layers until event has been handled
			for(auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
				if(e.isHandled()) break;
				(*it)->onEvent(e);
			}
		}

		void Application::run() {
			GE_Info("Starting Application...");
			/* 
			 * The OpenGL code here is only temporary 
			 * This will be abtracted and extracted into classes
			 * to swap choose later between OpenGL and DirectX
			*/
			glClearColor(0.f, 0.f, 0.f, 1.f);

			while(running) {
				if(!minimized) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					shader->bind();
					glBindVertexArray(vertexArray);
					glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

					{
						for(ge::core::Layer* layer : layerStack)
							layer->onUpdate();
					}
					{
						imGuiLayer->begin();
						for(ge::core::Layer* layer : layerStack) {
							layer->onImGUIRender();
						}
						imGuiLayer->end();
					}
				}

				window->onUpdate();
			}
		}

		bool Application::onWindowClose(ge::core::WindowCloseEvent& e) {
			running = false;
			return true;
		}
		bool Application::onWindowResize(ge::core::WindowResizeEvent& e) {
			if(e.getWidth() == 0 || e.getHeight() == 0) {
				minimized = true;
				return false;
			}
			minimized = false;
			
			return false;
		}
	}
}
