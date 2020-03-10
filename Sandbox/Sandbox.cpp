#include "sandboxPCH.h"

// TODO: move to QED.h
#include "imgui.h"
#include "ImGuiLayer.h"

#include "QED.h"

// TODO: Make memory leak detection

using namespace QED::Engine;


class SandboxLayer : public Layer::Layer
{
	public:
	// Construtor
	SandboxLayer() : Layer::Layer("SandboxLayer", true)
	{
		LOG << "Sandbox layer ctor";
	}

	public:
	// Override inherited pure virtual destructor
	virtual ~SandboxLayer() override
	{
		std::cout << "Sandbox layer dtor" << std::endl;
	};

	public:
	// Get name for module interface
	QED_MODULE_API virtual const char* GetName() const override
	{
		return "SandboxLayer";
	}

	public:
	// Override layer's OnUpdate method
	virtual void OnUpdate() override
	{
		if (Input::CoreInput::IsKeyPressed(Input::key_SPACE))
		{
			LOG << "Space!";
		}
	}

	public:
	// Override layer's OnUIRender method
	virtual void OnUIRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello from main");
		ImGui::End();
	}

};

// Register the module to the engine kernel
extern "C" QED_MODULE_API void Register(QED::Engine::Module::Module& module)
{
	// Set module name
	module.moduleName = "Sandbox";

	// Send back interface instances
	SandboxLayer* sandboxLayer = new SandboxLayer();
	sandboxLayer->Initialize();
	module.interfaces.emplace_back((Module::Interfaces::ModuleInterface*)sandboxLayer);
}
