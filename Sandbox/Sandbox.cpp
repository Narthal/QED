#include "sandboxPCH.h"
#include "QED.h"

#include "imgui.h"
#include "ImGuiLayer.h"

// TODO: Make memory leak detection

using namespace QED::Engine;


class SandboxLayer : public Layer::Layer
{
public:
	SandboxLayer() : Layer::Layer("SandboxLayer", true) {}

	virtual ~SandboxLayer() = default;

	virtual void OnUpdate() override
	{
		if (Input::CoreInput::IsKeyPressed(Input::key_SPACE))
		{
			//LOG << "Space!";
		}
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello from main");
		ImGui::End();
	}

private:

};

int main(int argc, char argv)
{
	auto& app = QED::Engine::Core::Application::Application::GetInstance();
	app.Initialize();

	app.PushLayer(new SandboxLayer());

	app.RunMainLoop();

	app.~Application();

	return 0;
}