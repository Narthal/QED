#include "sandboxPCH.h"

#include "QED.h"

// TODO: move this (custom types)
#include <glm\ext\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Sandbox2D.h"

namespace QED
{
	namespace Sandbox
	{
		class Sandbox : public Engine::Module::Interfaces::ModuleInterface
		{
		public:
			// Construtor
			Sandbox()
			{
				QED_PROFILE_FUNCTION();

				QED_CLIENT_LOG_INFO("Sandbox layer ctor");
			}

			// Override inherited pure virtual destructor
			virtual ~Sandbox() override
			{
				QED_PROFILE_FUNCTION();

				QED_CLIENT_LOG_INFO("Sandbox layer dtor");
			};

			// Module initialziation
			QED_MODULE_API virtual void Initialize() override
			{
				QED_PROFILE_FUNCTION();

				auto& instance = Interface::Core::Application::Application::GetApplication();

				instance.PushLayer(new Sandbox2D());
			}

			// Get name for module interface
			QED_MODULE_API virtual const char* GetName() const override
			{
				QED_PROFILE_FUNCTION();

				return "SandboxLayer";
			}
		};
	}
}



// Register the module to the engine kernel
extern "C" QED_MODULE_API void Register(QED::Engine::Module::Module& module)
{
	// Set module name
	module.moduleName = "Sandbox";

	// Send back interface instances
	QED::Sandbox::Sandbox* sandbox = new QED::Sandbox::Sandbox();
	sandbox->Initialize();
	module.interfaces.emplace_back((QED::Engine::Module::Interfaces::ModuleInterface*)sandbox);
}
