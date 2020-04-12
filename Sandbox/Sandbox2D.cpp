#include "SandboxPCH.h"
#include "Sandbox2D.h"

#include <glm\ext\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace QED
{
	namespace Sandbox
	{
		Sandbox2D::Sandbox2D() : Engine::Layer::Layer("Sandbox2D"), cameraController(1280.0f / 720.0f, true)
		{
			
		}

		void Sandbox2D::OnAttach()
		{
			QED_CLIENT_LOG_INFO("Sandbox2D layer attach");

			vertexArray = Engine::Graphics::VertexArray::Create();
			float vertices[3 * 4] =
			{
				-0.5f, -0.5f,  0.0f,
				 0.5f, -0.5f,  0.0f,
				 0.5f,  0.5f,  0.0f,
				-0.5f,  0.5f,  0.0f,
			};

			Ref<Engine::Graphics::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Engine::Graphics::VertexBuffer::Create(vertices, sizeof(vertices)));
			vertexBuffer->SetLayout
			({
				{ Engine::Graphics::ShaderDataType::Float3, "aPosition" }
			});
			vertexArray->AddVertexBuffer(vertexBuffer);

			unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
			Ref<Engine::Graphics::IndexBuffer> indexBuffer;
			indexBuffer.reset(Engine::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			vertexArray->SetIndexBuffer(indexBuffer);

			shader = Engine::Graphics::Shader::Create("FlatColor.glsl");

		}

		void Sandbox2D::OnDetach()
		{
		}

		void Sandbox2D::OnUpdate(Engine::Core::Time::TimeStep timeStep)
		{
			// Update camera
			cameraController.OnUpdate(timeStep);

			// Render

			// Clear
			Engine::Graphics::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			Engine::Graphics::RenderCommand::Clear();

			// Scene
			Engine::Graphics::Renderer::BeginScene(cameraController.GetCamera());

			shader->Bind();
			shader->UploadUniformFloat4("uColor", squareColor);

			Engine::Graphics::Renderer::Submit(shader, vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.2f)));

			Engine::Graphics::Renderer::EndScene();
		}

		void Sandbox2D::OnUIRender()
		{
			ImGui::Begin("Settings");
			ImGui::ColorEdit3("Square color", glm::value_ptr(squareColor));
			ImGui::End();
		}

		void Sandbox2D::OnEvent(Engine::Event::Event& event)
		{
			cameraController.OnEvent(event);
		}
	}
}
