#include "EnginePCH.h"
#include "Application.h"


#include "../Log/Log.h"


#include "../Window/GLFWWindow.h"


#define BIND_EVENT_FUCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::Initialize()
			{
				window = new Window::GLFWWindow();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));
			}

			void Application::Application::OnEvent(Event::Event& event)
			{
				Event::EventDispatcher dispatcher(event);
				dispatcher.Dispatch<Event::WindowCloseEvent>(BIND_EVENT_FUCTION(Application::OnWindowClose));

				Log::LogLine() << event;
			}


			void Application::Application::RunMainLoop()
			{
				while (isRunning)
				{
					window->Update();
					//std::cout << "a" << std::endl;
				};
			}
			bool Application::Application::OnWindowClose(Event::WindowCloseEvent& event)
			{
				isRunning = false;
				return true;
			}
		}
	}
}


