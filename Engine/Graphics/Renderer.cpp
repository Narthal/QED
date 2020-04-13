#include "enginePCH.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Renderer2D.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Scope<Renderer::SceneData> Renderer::sceneData = Core::Type::CreateScope<Renderer::SceneData>();

			void Renderer::Initialize()
			{
				RenderCommand::Initialize();
				Renderer2D::Initialize();
			}

			void Renderer::OnWindowResize(uint32_t width, uint32_t height)
			{
				RenderCommand::SetViewport(0, 0, width, height);
			}

			void Renderer::BeginScene(OrthographicCamera& camera)
			{
				sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
			}

			void Renderer::EndScene()
			{
			}

			void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
			{
				// Shader
				shader->Bind();
				shader->SetMat4("uViewProjection", sceneData->viewProjectionMatrix);

				shader->SetMat4("uTransform", transform);

				// VAO
				vertexArray->Bind();

				// Draw
				RenderCommand::Draw(vertexArray);
			}
		}
	}
}