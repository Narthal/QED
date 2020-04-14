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

			texture = Engine::Graphics::Texture2D::Create("glider.png");
		}

		void Sandbox2D::OnDetach()
		{
		}

		void Sandbox2D::OnUpdate(Engine::Core::Time::TimeStep timeStep)
		{
			Engine::Profiler::Timer timer("Sandbox2D::OnUpdate", [&](auto& profileResult) { profileResults.push_back(profileResult); });

			// Update camera
			cameraController.OnUpdate(timeStep);

			// Render

			// Clear
			Engine::Graphics::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			Engine::Graphics::RenderCommand::Clear();

			// Scene
			Engine::Graphics::Renderer2D::BeginScene(cameraController.GetCamera());

			Engine::Graphics::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 0.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			Engine::Graphics::Renderer2D::DrawQuad({ 0.0f, -0.5f }, { 0.5f, 0.75f }, counter, { 0.2f, 0.3f, 0.8f, 1.0f });
			Engine::Graphics::Renderer2D::DrawQuad({ 0.2f, 0.5f }, { 0.5f, 0.5f }, 0.0f, texture);

			counter++;

			Engine::Graphics::Renderer2D::EndScene();
		}

		void Sandbox2D::OnUIRender()
		{
			Engine::Profiler::Timer timer("Sandbox2D::OnUIRender", [&](auto& profileResult) { profileResults.push_back(profileResult); });

			ImGui::Begin("Settings");
			
			ImGui::ColorEdit3("Square color", glm::value_ptr(squareColor));
			
			for (auto& result : profileResults)
			{
				char label[50];
				strcpy(label, result.name);
				strcat(label, " %.3f");
				ImGui::Text(label, result.time);
			}
			profileResults.clear();

			ImGui::End();
		}

		void Sandbox2D::OnEvent(Engine::Event::Event& event)
		{
			cameraController.OnEvent(event);
		}
	}
}
