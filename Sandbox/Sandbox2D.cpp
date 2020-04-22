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

			texture1 = Engine::Graphics::Interface::Textures::Texture2D::Create("twitter.png");
			texture2 = Engine::Graphics::Interface::Textures::Texture2D::Create("glider.png");
		}

		void Sandbox2D::OnDetach()
		{
		}

		void Sandbox2D::OnUpdate(Engine::Core::Time::TimeStep timeStep)
		{
			QED_PROFILE_FUNCTION();

			// Update camera
			{
				QED_PROFILE_SCOPE("Sandbox2D::OnUpdate Camera");
				cameraController.OnUpdate(timeStep);
			}

			// Render
			Engine::Graphics::Renderer::Renderer2D::ResetStatistics();

			// Clear
			Engine::Graphics::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			Engine::Graphics::Renderer::RenderCommand::Clear();

			// Scene
			{
				QED_PROFILE_SCOPE("Sandbox2D::OnUpdate Render scene");
				Engine::Graphics::Renderer::Renderer2D::BeginScene(cameraController.GetCamera());

				Engine::Graphics::Renderer::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 0.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
				Engine::Graphics::Renderer::Renderer2D::DrawQuad({ 0.0f, -0.5f }, { 0.5f, 0.75f }, 0.0f, { 0.2f, 0.3f, 0.8f, 1.0f });
				Engine::Graphics::Renderer::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 0.5f, 0.5f }, counter, texture1, { 1.0f, 0.0f, 0.0f, 1.0f }, 2.0f);

				counter++;

				//Engine::Graphics::Renderer::Renderer2D::EndScene();


				//Engine::Graphics::Renderer::Renderer2D::BeginScene(cameraController.GetCamera());
				int testCounter = 0;
				const float increment = 0.5f;
				for (float y = -5.0f; y < 5.0f; y += increment)
				{
					for (float x = -5.0f; x < 5.0f; x += increment)
					{
						glm::vec4 rg = { (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.0f, 0.5f };
						Engine::Graphics::Renderer::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, 0.0f, rg);
						testCounter++;
					}
				}

				Engine::Graphics::Renderer::Renderer2D::DrawQuad({ -0.5f, -0.7f, 0.1f }, { 0.5f, 0.5f }, 0.0f, texture1, 1.0f);

				Engine::Graphics::Renderer::Renderer2D::EndScene();
			}
		}

		void Sandbox2D::OnUIRender()
		{
			QED_PROFILE_FUNCTION();

			ImGui::Begin("Settings");
			
			auto stats = Engine::Graphics::Renderer::Renderer2D::GetStatistics();
			ImGui::Text("Renderer2D Stats");
			ImGui::Text("Draw calls: %d", stats.drawCalls);
			ImGui::Text("Quad count: %d", stats.quadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

			ImGui::ColorEdit3("Square color", glm::value_ptr(squareColor));

			ImGui::End();
		}

		void Sandbox2D::OnEvent(Engine::Event::Event& event)
		{
			cameraController.OnEvent(event);
		}
	}
}
