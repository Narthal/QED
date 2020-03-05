#include "EnginePCH.h"

#include "Application/Application.h"

int main(int argc, char argv)
{
	auto& app = QED::Engine::Core::Application::Application::GetInstance();
	app.Initialize();

	app.RunMainLoop();

	app.~Application();

	return 0;
}