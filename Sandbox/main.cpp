#include "sandboxPCH.h"
#include "QED.h"



int main(int argc, char argv)
{
	auto& app = QED::Engine::Core::Application::Application::GetInstance();
	app.PushOverlay(new QED::Engine::UI::ImGuiLayer);
	app.RunMainLoop();

	return 0;
}