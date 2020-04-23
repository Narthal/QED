#include "EnginePCH.h"
#include "ApplicationInterface.h"

#include "Application.h"

namespace QED
{
	namespace Interface
	{
		namespace Core
		{
			namespace Application
			{
				Application& Application::GetApplication()
				{
					static Application applicationInterface;
					applicationInterface.application = &Engine::Core::Application::Application::GetInstance();
					return applicationInterface;
				}

				void Application::PushLayer(QED::Engine::Layer::Layer* layer)
				{
					application->PushLayer(layer);
				}
			}
		}
	}
}