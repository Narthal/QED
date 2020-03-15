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

// Graphics
#include "../Graphics/BufferLayout.h"







namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			static GLenum ShdaerDataTypeToOpenGL(Graphics::ShaderDataType shaderDataType)
			{
				switch (shaderDataType)
				{
					// NONE
					case QED::Engine::Graphics::ShaderDataType::NONE:
					// TODO: crash here
					break;

					// Floats
					case QED::Engine::Graphics::ShaderDataType::Float:		return GL_FLOAT;
					case QED::Engine::Graphics::ShaderDataType::Float2:		return GL_FLOAT;
					case QED::Engine::Graphics::ShaderDataType::Float3:		return GL_FLOAT;
					case QED::Engine::Graphics::ShaderDataType::Float4:		return GL_FLOAT;

					// Matrices
					case QED::Engine::Graphics::ShaderDataType::Mat3:		return GL_FLOAT;
					case QED::Engine::Graphics::ShaderDataType::Mat4:		return GL_FLOAT;

					// Integers
					case QED::Engine::Graphics::ShaderDataType::Int:		return GL_INT;
					case QED::Engine::Graphics::ShaderDataType::Int2:		return GL_INT;
					case QED::Engine::Graphics::ShaderDataType::Int3:		return GL_INT;
					case QED::Engine::Graphics::ShaderDataType::Int4:		return GL_INT;

					// Boolean
					case QED::Engine::Graphics::ShaderDataType::Bool:		return GL_BOOL;

					// Default
					default:
					// TODO: crash here
					break;
				}

				// TODO: crash here
				return -1;
			}

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



				float vertices[3 * (3 + 4)] =
				{
					-0.5f, -0.5f,  0.0f,	1.0f, 0.0f,  1.0f, 1.0f,
					 0.5f, -0.5f,  0.0f,	0.0f, 1.0f,  1.0f, 1.0f,
					 0.0f,  0.5f,  0.0f,	1.0f, 1.0f,  0.0f, 1.0f,
				};
				vertexBuffer.reset(Graphics::VertexBuffer::Create(vertices, sizeof(vertices)));

				{
					Graphics::BufferLayout layout =
					{
						{ Graphics::ShaderDataType::Float3, "aPosition" },
						{ Graphics::ShaderDataType::Float4, "aColor" },
					};

					vertexBuffer->SetLayout(layout);
				}

				uint32_t index = 0;
				for (const auto& element : vertexBuffer->GetLayout())
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer
					(
						index,
						element.GetComponentCount(),
						ShdaerDataTypeToOpenGL(element.shaderDataType),
						element.normalized ? GL_TRUE : GL_FALSE,
						vertexBuffer->GetLayout().GetStride(),
						(const void*)element.offset
					);
					index++;
				}



				unsigned int indices[3] = { 0, 1, 2 };
				indexBuffer.reset(Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));



				std::string vertexSource =
				R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;
					layout(location = 1) in vec4 aColor;

					out vec3 vPosition;
					out vec4 vColor;

					void main()
					{
						vPosition = aPosition;
						vColor = aColor;

						gl_Position = vec4(aPosition, 1.0);
					}
				)";

				std::string fragmentSource =
				R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;
					in vec4 vColor;

					void main()
					{
						color = vec4((vPosition + 1) / 2, 1.0);
						color = vColor;
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


