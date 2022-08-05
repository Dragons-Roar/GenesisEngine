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

			std::unique_ptr<Shader> shader;
			IVertexBuffer* vertexBuffer;
			IIndexBuffer* indexBuffer;

			GLuint vertexArray;

			ImGUILayer* imGuiLayer;
		};

		// To be defined in Sandbox
		Application* createApplication();
	}
}
