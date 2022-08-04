#include <GenesisClientCore/Application.hpp>
#include <GenesisClientCore/imgui/ImGUILayer.hpp>
#include <GenesisClientCore/Input.hpp>

namespace ge {
	namespace clientcore {
		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& config): appConfig(config) {
			if(instance) std::cerr << "Application already exists!" << std::endl;
			instance = this;

			window = IWindow::create(WindowProps(config.name));
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));

			layerStack.pushLayer(new ge::clientcore::ImGUILayer());
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
			while(running) {
				if(!minimized) {
					{
						for(ge::core::Layer* layer : layerStack)
							layer->onUpdate();
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
