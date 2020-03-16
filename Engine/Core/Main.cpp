#include "EnginePCH.h"

#include "Application/Application.h"




int main(int argc, char argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create application instance
	auto& app = QED::Engine::Core::Application::Application::GetInstance();

	// NOTE: initialize called after application constructor, so this pointer exists in initialization code
	app.Initialize();

	// NOTE: calling main loop from main ensures that initialization succeeded
	app.RunMainLoop();

	// Destroy application and all its components on exit
	app.~Application();

	return 0;
}