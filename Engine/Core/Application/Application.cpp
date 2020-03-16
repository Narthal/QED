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
			void Application::Application::Initialize()
			{
				// Set up main loop variable
				isRunning = true;

				// Create window
				window = std::make_unique<Window::GLFWWindow>();
				window->SetEventCallback(BIND_EVENT_FUCTION(Application::OnEvent));

				// Initialize input
				Input::CoreInput::GetInstance();

				// Add ImGui layer to layer stack
				UILayer = new UI::ImGuiLayer();
				PushOverlay(UILayer);

				LOG << "init";

				kernel = new Module::Kernel;


				// Test
				vertexArray.reset(Graphics::VertexArray::Create());

				float vertices[3 * (3 + 4)] =
				{
					-0.5f, -0.5f,  0.0f,	1.0f, 0.0f,  1.0f, 1.0f,
					 0.5f, -0.5f,  0.0f,	0.0f, 1.0f,  1.0f, 1.0f,
					 0.0f,  0.5f,  0.0f,	1.0f, 1.0f,  0.0f, 1.0f,
				};

				std::shared_ptr<Graphics::VertexBuffer> vertexBuffer;
				vertexBuffer.reset(Graphics::VertexBuffer::Create(vertices, sizeof(vertices)));

				{
					Graphics::BufferLayout layout =
					{
						{ Graphics::ShaderDataType::Float3, "aPosition" },
						{ Graphics::ShaderDataType::Float4, "aColor" },
					};

					vertexBuffer->SetLayout(layout);
				}

				vertexArray->AddVertexBuffer(vertexBuffer);

				unsigned int indices[3] = { 0, 1, 2 };
				std::shared_ptr<Graphics::IndexBuffer> indexBuffer;
				indexBuffer.reset(Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
				vertexArray->SetIndexBuffer(indexBuffer);

				// square
				squareVA.reset(Graphics::VertexArray::Create());
				float squareVertices[3 * 4] =
				{
					-0.5f, -0.5f,  0.0f,
					 0.5f, -0.5f,  0.0f,
					 0.5f,  0.5f,  0.0f,
					-0.5f,  0.5f,  0.0f,
				};
				
				std::shared_ptr<Graphics::VertexBuffer> squareVB;
				squareVB.reset(Graphics::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
				squareVB->SetLayout
				({
					{ Graphics::ShaderDataType::Float3, "aPosition" },
				});
				squareVA->AddVertexBuffer(squareVB);

				unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
				std::shared_ptr<Graphics::IndexBuffer> squareIB;
				squareIB.reset(Graphics::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
				squareVA->SetIndexBuffer(squareIB);


				std::string squareVertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;

					out vec3 vPosition;

					void main()
					{
						vPosition = aPosition;

						gl_Position = vec4(aPosition, 1.0);
					}
				)";

				std::string squareFragmentSource =
					R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;

					void main()
					{
						color = vec4((vPosition + 1) / 2, 1.0);
					}
				)";

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
				squareShader.reset(Graphics::Shader::Create(squareVertexSource, squareFragmentSource));
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
					squareShader->Bind();
					squareVA->Bind();
					glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

					shader->Bind();
					vertexArray->Bind();
					glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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


