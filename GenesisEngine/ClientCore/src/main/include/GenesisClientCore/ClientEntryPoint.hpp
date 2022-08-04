#pragma once
#include "./Application.hpp"

#ifdef GE_WINDOWS
extern ge::clientcore::Application* ge::clientcore::createApplication();

int main(int argc, char** argv)
{
	// TODO: Init Logger and some other stuff
	auto app = ge::clientcore::createApplication();
	app->run();

	delete app;
}
#endif
