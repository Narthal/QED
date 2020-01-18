#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#include "Application.h"



extern QED::Engine::Core::Application::Application* QED::Engine::Core::Application::CreateApplication();

int main(int argc, char argv)
{
	auto app = QED::Engine::Core::Application::CreateApplication();
	app->RunMainLoop();
	delete app;

	return 0;
}

#endif // !ENTRY_POINT_H
