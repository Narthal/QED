#include "EnginePCH.h"
#include "Application.h"


#include "../Log/Log.h"
#include "../Window/GLFWWindow.h"



#include "glad/glad.h"





namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::Initialize()
			{
				isRunning = true;

				window = new Window::GLFWWindow();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));

				LOG << "init";
			}

			void Application::Application::OnEvent(Event::Event& event)
			{
				// Handle window close
				Event::EventDispatcher dispatcher(event);
				dispatcher.Dispatch<Event::WindowCloseEvent>(BIND_EVENT_FUCTION(Application::OnWindowClose));

				// Handle layers
				for (auto it = layerStack.end(); it != layerStack.begin();)
				{
					(*--it)->OnEvent(event);
					if (event.handled)
					{
						break;
					}
				}


				LOG << event;
			}


			void Application::Application::RunMainLoop()
			{
				while (isRunning)
				{
					glClearColor(0, 0, 0, 1);
					glClear(GL_COLOR_BUFFER_BIT);

					for (Layer::Layer* layer : layerStack)
					{
						layer->OnUpdate();
					}

					window->Update();
				};
			}

			void Application::Application::PushLayer(Layer::Layer* layer)
			{
				layerStack.PushLayer(layer);
			}

			void Application::Application::PushOverlay(Layer::Layer* overlay)
			{
				layerStack.PushOverlay(overlay);
			}

			bool Application::Application::OnWindowClose(Event::WindowCloseEvent& event)
			{
				isRunning = false;
				return true;
			}
		}
	}
}


