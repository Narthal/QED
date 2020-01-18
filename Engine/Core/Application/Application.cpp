#include "EnginePCH.h"
#include "Application.h"

// TODO: remove this
#include "../Log/Log.h"


#include "../Window/GLFWWindow.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::Initialize()
			{
				window = new Window::GLFWWindow();
			}


			void Application::Application::RunMainLoop()
			{
				while (isRunning)
				{
					window->Update();
					std::cout << "a" << std::endl;
				};
			}
		}
	}
}


