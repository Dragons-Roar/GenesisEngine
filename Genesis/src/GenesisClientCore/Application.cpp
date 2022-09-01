#include "Application.hpp"

#include <GenesisClientCore/command/impl/CommandHello.hpp>
#include <GenesisCore/Logger.hpp>
#include <GenesisCore/command/CommandManager.hpp>

#include "GenesisClientCore/Defines.hpp"
#include "GenesisClientCore/Input.hpp"
#include "GenesisClientCore/Platform.hpp"
#include "GenesisClientCore/command/impl/CommandWireframe.hpp"
#include "GenesisClientCore/imgui/ImGUILayer.hpp"
#include "GenesisClientCore/renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

void stdIn() {
	String in;
	while(ge::clientcore::Application::getInstance().isRunning()) {
		std::getline(std::cin, in);

		if(in.empty()) continue;
		if(in.rfind('/', 0) != 0) continue;
		ge::core::CommandManager::runCommand(in.substr(1));
	}
}

namespace ge {
	namespace clientcore {
		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& config): appConfig(config), stdInThread(stdIn) {
			GE_ProfileFunction();

			GE_Assert(!instance, "Instance already exists!");
			instance = this;

			window = IWindow::create(WindowProps(config.name, config.width, config.height));
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));
			window->setVSync(true);

			Renderer::init();

			imGuiLayer = new ImGUILayer();
			layerStack.pushOverlay(imGuiLayer);

			ge::core::CommandManager::init();
			GE_Info("Initializing Client Commands...");
			ge::core::CommandManager::addCommand(ge::core::CreateRef<CommandWireframe>());
			ge::core::CommandManager::addCommand(ge::core::CreateRef<CommandHello>());
		}
		Application::~Application() {
		}

		void Application::close() {
			running = false;
		}

		void Application::onEvent(ge::core::Event& e) {
			GE_ProfileFunction();

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
			RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});

			while(running) {
				GE_ProfileScope("Application Loop");

				float32 time = Platform::getTime();
				ge::core::Timestep timestep = time - lastTime;
				lastTime = time;

				if(!minimized) {
					for(ge::core::Layer* layer: layerStack) {
						layer->onUpdate(timestep);
					}
				}

				{
					imGuiLayer->begin();
					for(ge::core::Layer* layer: layerStack) {
						layer->onImGUIRender();
					}
					imGuiLayer->end();
				}

				window->onUpdate();
			}

			ge::core::CommandManager::shutdown();
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
			Renderer::onWindowResize(e.getWidth(), e.getHeight());

			return false;
		}
	}
}
