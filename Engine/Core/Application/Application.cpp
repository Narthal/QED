#include "EnginePCH.h"
#include "Application.h"

// OpenGL
#include <glad/glad.h>



// Log
#include "../Log/Log.h"

// Window
#include "../Window/GLFWWindow.h"

// Events
#include "../Input/CoreInput.h"

// UI
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



				float vertices[3 * 3] =
				{
					-0.5f, -0.5f,  0.0f,
					 0.5f, -0.5f,  0.0f,
					 0.0f,  0.5f,  0.0f
				};
				vertexBuffer.reset(Graphics::VertexBuffer::Create(vertices, sizeof(vertices)));

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

				unsigned int indices[3] = { 0, 1,2 };
				indexBuffer.reset(Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));



				std::string vertexSource =
				R"(
					#version 330 core
					
					layout(location = 0) in vec3 attributePosition;

					out vec3 varyingPosition;

					void main()
					{
						varyingPosition = attributePosition;
						gl_Position = vec4(attributePosition, 1.0);
					}
				)";

				std::string fragmentSource =
				R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 varyingPosition;

					void main()
					{
						color = vec4((varyingPosition + 1) / 2, 1.0);
					}
				)";

				shader.reset(Graphics::Shader::Create(vertexSource, fragmentSource));
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
					shader->Bind();
					glBindVertexArray(vertexArrayID);
					glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

				// Test
				// TODO: remove
				shader.release();
				vertexBuffer.release();
				indexBuffer.release();

				return true;
			}
		}
	}
}


