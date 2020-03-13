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
				UILayer = new UI::ImGuiLayer();
				PushOverlay(UILayer);

				LOG << "init";

				kernel = new Module::Kernel;


				// Test
				glGenVertexArrays(1, &vertexArrayID);
				glBindVertexArray(vertexArrayID);

				glGenBuffers(1, &vertexBufferID);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

				float vertices[3 * 3] =
				{
					-0.5f, -0.5f,  0.0f,
					 0.5f, -0.5f,  0.0f,
					 0.0f,  0.5f,  0.0f
				};
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

				glGenBuffers(1, &indexBufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

				unsigned int indices[3] = { 0, 1,2 };
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
					// Clear
					glClearColor(0, 0, 0, 1);
					glClear(GL_COLOR_BUFFER_BIT);

					// Test
					glBindVertexArray(vertexArrayID);
					glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

					// OnUpdate loop
					for (Layer::Layer* layer : layerStack)
					{
						layer->OnUpdate();
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
		}
	}
}


