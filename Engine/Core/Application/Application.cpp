#include "EnginePCH.h"
#include "Application.h"

// TODO: move this
#include <GLFW\glfw3.h>

// Log
#include "Core/Log/Log.h"

// Window
#include "Window/GLFWWindow.h"

// Time
#include "Core/Time/TimeStep.h"

// Events
#include "Input/CoreInput.h"

// UI
#include "UI/ImGuiLayer.h"

// Graphics
#include "Graphics/Interface/Buffers/BufferLayout.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderCommand.h"

#include "Profiler/Instrumentor.h"




namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::Initialize()
			{
				QED_PROFILE_FUNCTION();

				// Set up main loop variable
				isRunning = true;

				// Setup logger
				Log::Initialize();
				QED_CORE_LOG_INFO("Core logger initialized");

				// Create window
				window = Type::CreateScope<Window::GLFWWindow>();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));

				Graphics::RenderCommand::SetViewport(0, 0, window->GetWidth(), window->GetHeight());

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
				QED_PROFILE_FUNCTION();

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
				QED_PROFILE_FUNCTION();

				while (isRunning)
				{
					float time = (float)glfwGetTime();
					Time::TimeStep timeStep = time - lastFrameTime;
					lastFrameTime = time;

					if (!minimized)
					{
						{
							QED_PROFILE_SCOPE("Application::RunMainLoop Update")
							// OnUpdate loop

							for (Layer::Layer* layer : layerStack)
							{
								layer->OnUpdate(timeStep);
							}
						}

						{
							QED_PROFILE_SCOPE("Application::RunMainLoop UIUpdate")
							// OnUIRender loop
							UILayer->Begin();
							for (Layer::Layer* layer : layerStack)
							{
								layer->OnUIRender();
							}
							UILayer->End();
						}
					}

					{
						QED_PROFILE_SCOPE("Application::RunMainLoop WindowUpdate")
						// Window update tick
						window->OnUpdate();
					}
				};
			}

			void Application::Application::PushLayer(Layer::Layer* layer)
			{
				QED_PROFILE_FUNCTION();

				layerStack.PushLayer(layer);
			}

			void Application::Application::PushOverlay(Layer::Layer* overlay)
			{
				QED_PROFILE_FUNCTION();

				layerStack.PushOverlay(overlay);
			}

			bool Application::Application::OnWindowClose(Event::WindowCloseEvent& event)
			{
				QED_PROFILE_FUNCTION();

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
				QED_PROFILE_FUNCTION();

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


