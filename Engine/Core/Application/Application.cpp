#include "EnginePCH.h"
#include "Application.h"

// TODO: move this
#include <GLFW\glfw3.h>

// Log
#include "../Log/Log.h"

// Window
#include "../Window/GLFWWindow.h"

// Time
#include "../Time/TimeStep.h"

// Events
#include "../Input/CoreInput.h"

// UI
#include "../../UI/ImGuiLayer.h"

// Graphics
#include "../Graphics/BufferLayout.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderCommand.h"




namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::Initialize()
			{
				// Set up main loop variable
				isRunning = true;

				// Setup logger
				Log::Initialize();
				QED_CORE_LOG_INFO("Core logger initialized");

				// Create window
				window = std::make_unique<Window::GLFWWindow>();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));

				// Initialize renderer
				Graphics::Renderer::Initialize();

				// Add ImGui layer to layer stack
				UILayer = new UI::ImGuiLayer();
				PushOverlay(UILayer);

				// Init kernel
				kernel = new Module::Kernel;

				QED_CORE_LOG_INFO("QED application initialization finished");
			}

			void Application::Application::OnEvent(Event::Event& event)
			{
				// Handle window close
				Event::EventDispatcher dispatcher(event);
				dispatcher.Dispatch<Event::WindowCloseEvent>(BIND_EVENT_FUCTION(Application::OnWindowClose));
				dispatcher.Dispatch<Event::WindowResizeEvent>(BIND_EVENT_FUCTION(Application::OnWindowResize));

				// Handle layers
				for (auto it = layerStack.end(); it != layerStack.begin();)
				{
					(*--it)->OnEvent(event);
					if (event.handled)
					{
						break;
					}
				}
			}

			void Application::Application::RunMainLoop()
			{
				while (isRunning)
				{
					float time = (float)glfwGetTime();
					Time::TimeStep timeStep = time - lastFrameTime;
					lastFrameTime = time;

					// OnUpdate loop
					if (!minimized)
					{
						for (Layer::Layer* layer : layerStack)
						{
							layer->OnUpdate(timeStep);
						}
					}

					// OnUIRender loop
					UILayer->Begin();
					for (Layer::Layer* layer : layerStack)
					{
						layer->OnUIRender();
					}
					UILayer->End();

					// Window update tick
					window->OnUpdate();
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
				// Set running flag to false (closing main loop)
				isRunning = false;

				// Clear layers
				layerStack.~LayerStack();

				// Unload modules (thus destructing all interface instances contained)
				delete kernel;

				return true;
			}

			bool Application::Application::OnWindowResize(Event::WindowResizeEvent& event)
			{
				if (event.GetWidth() == 0 || event.GetHeight() == 0)
				{
					minimized = true;
					return false;
				}

				Graphics::Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

				minimized = false;
				return false;
			}
		}
	}
}


