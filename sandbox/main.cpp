#include "QED.h"


class Sandbox : public QED::Engine::Core::Application::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

private:

};




QED::Engine::Core::Application::Application* QED::Engine::Core::Application::CreateApplication()
{
	QED::Engine::Core::Globals::registry->instance().Set("someData1", "data1");
	QED::Engine::Core::Globals::registry->instance().Set("someData2", "data2");

	QED::Engine::Core::Log::LogLine() << QED::Engine::Core::Globals::registry->instance().Get("someData2") << " " << QED::Engine::Core::Globals::registry->instance().Get("someData1");


	return new Sandbox();
}