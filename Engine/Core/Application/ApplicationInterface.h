#ifndef APPLICATION_INTERFACE_H
#define APPLICATION_INTERFACE_H

#include "Module/QEDApi.h"

namespace QED::Engine::Core::Application
{
	class Application;
}

namespace QED::Engine::Layer
{
	class Layer;
}

namespace QED
{
	namespace Interface
	{
		namespace Core
		{
			namespace Application
			{
				class QED_ENGINE_API Application
				{
				public:
					static Application& GetApplication();

				public:
					void PushLayer(QED::Engine::Layer::Layer* layer);

				private:
					Engine::Core::Application::Application* application;
				};
			}
		}
	}
}

#endif // !APPLICATION_INTERFACE_H
