#include "sandboxPCH.h"
#include "QED.h"



int main(int argc, char argv)
{
	auto app = new QED::Engine::Core::Application::Application();
	app->RunMainLoop();
	delete app;

	return 0;
}