#pragma once
#include "GenesisClientCore/Application.hpp"
#include <GenesisCore/Logger.hpp>

#ifdef GE_WINDOWS
	#include <Windows.h>
	extern ge::clientcore::Application* ge::clientcore::createApplication();

	#ifndef GE_DIST
		int main(int argc, char** argv) {
			ge::core::Logger::init();
			GE_Info("Initialized Logger!");

			auto app = ge::clientcore::createApplication();
			app->run();

			delete app;
			return 0;
		}
	#else
		int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
			ge::core::Logger::init();
			GE_Info("Initialized Logger!");

			auto app = ge::clientcore::createApplication();
			app->run();

			delete app;
			return 0;
		}
	#endif
#endif
