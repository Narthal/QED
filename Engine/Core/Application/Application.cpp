#include "EnginePCH.h"
#include "Application.h"


#include "glad/glad.h"



#include "../Log/Log.h"
#include "../Window/GLFWWindow.h"
#include "../Input/CoreInput.h"
#include "../../UI/ImGuiLayer.h"









namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			//Application::Application* Application::Application::instance;

			void Application::Application::Initialize()
			{
				// Set up main loop variable
				isRunning = true;

				// Create window
				window = new Window::GLFWWindow();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));

				// Initialize input
				Input::CoreInput::GetInstance();

				// Add ImGui layer to layer stack
				PushOverlay(new UI::ImGuiLayer());

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
						if (layer->IsUI() == true) ((UI::ImGuiLayer*)layer)->Begin();
						layer->OnUpdate();
						if (layer->IsUI() == true) ((UI::ImGuiLayer*)layer)->OnUIRender();
						if (layer->IsUI() == true) ((UI::ImGuiLayer*)layer)->End();
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


