#include "sandboxPCH.h"
#include "QED.h"




using namespace QED::Engine;




class SandboxLayer : public Layer::Layer
{
public:
	SandboxLayer() : Layer::Layer("SandboxLayer") {}

	virtual ~SandboxLayer() = default;

	virtual void OnUpdate() override
	{
		if (Input::CoreInput::IsKeyPressed(Input::key_SPACE))
		{
			//LOG << "Space!";
		}
	}

private:

};

int main(int argc, char argv)
{
	auto& app = QED::Engine::Core::Application::Application::GetInstance();
	app.Initialize();

	app.PushLayer(new SandboxLayer);

	app.RunMainLoop();

	return 0;
}