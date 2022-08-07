#pragma once
#include "./Defines.hpp"
#include "./Window.hpp"
#include <GenesisCore/event/Event.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <GenesisCore/event/MouseEvent.hpp>
#include <GenesisCore/event/WindowEvent.hpp>
#include <GenesisCore/LayerStack.hpp>

#include <GenesisClientCore/imgui/ImGUILayer.hpp>

#include "renderer/Shader.hpp"
#include "renderer/Buffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Camera.hpp"

#ifdef GE_WINDOWS
#	include <Windows.h>
#endif

// Temporary
#ifdef GE_OPENGL
#	include <glad/glad.h>
#endif

int main(int argc, char** argv);

namespace ge {
	namespace clientcore {
		struct ApplicationConfiguration {
		public:
			String name = "Genesis Application";
		};

		class Application {
		public:
			Application(const ApplicationConfiguration& config);
			virtual ~Application();

			void onEvent(ge::core::Event& e);

			IWindow& getWindow() { return *window; }

			void close();

			static Application& getInstance() { return *instance; }

			const ApplicationConfiguration& getAppConfig() const { return appConfig; }

			/// <summary>
			/// Push a new layer onto the application layer stack
			/// </summary>
			/// <param name="layer">The layer to push</param>
			inline void pushLayer(ge::core::Layer* layer) { layerStack.pushLayer(layer); }
			/// <summary>
			/// Push a new overlay onto the application layer stack (overlays will always be at the top)
			/// </summary>
			/// <param name="layer">The overlay to push</param>
			inline void pushOverlay(ge::core::Layer* layer) { layerStack.pushOverlay(layer); }
			/// <summary>
			/// Remove a layer from the application layer stack
			/// </summary>
			/// <param name="layer">The layer</param>
			inline void popLayer(ge::core::Layer* layer) { layerStack.popLayer(layer); }
			/// <summary>
			/// Remove a overlay from the application layer stack
			/// </summary>
			/// <param name="layer">The overlay</param>
			inline void popOverlay(ge::core::Layer* layer) { layerStack.popOverlay(layer); }

		private:
			void run();

			bool onWindowClose(ge::core::WindowCloseEvent& e);
			bool onWindowResize(ge::core::WindowResizeEvent& e);

		private:
			ApplicationConfiguration appConfig;
			IWindow* window;

			bool running = true;
			bool minimized = false;

			ge::core::LayerStack layerStack;

			static Application* instance;

			friend int ::main(int argc, char** argv);

			#ifdef GE_WINDOWS 
			#ifdef GE_DIST
			friend int ::wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
			#endif 
			#endif

			ImGUILayer* imGuiLayer;
		};

		// To be defined in Sandbox
		Application* createApplication();
	}
}
