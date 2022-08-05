#include <GenesisClientCore/Application.hpp>
#include <GenesisClientCore/imgui/ImGUILayer.hpp>
#include <GenesisClientCore/Input.hpp>
#include <GenesisCore/Logger.hpp>

#include <GLFW/glfw3.h>

namespace ge {
	namespace clientcore {
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


			float32 vertices[3 * 3] = {
				-.5f, -.5f, 0.f,
				 .5f, -.5f, 0.f,
				 0.f,  .5f, 0.f
			};

			vertexBuffer = IVertexBuffer::create(vertices, sizeof(vertices));

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float32), nullptr);

			uint32 indices[3] = { 0, 1, 2 };
			indexBuffer = IIndexBuffer::create(indices, sizeof(indices));

			shader = std::make_unique<Shader>("assets/shader/basic.vert", "assets/shader/basic.frag");
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
