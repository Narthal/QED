#include "enginePCH.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

			void Renderer::BeginScene(OrthographicCamera& camera)
			{
				sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
			}

			void Renderer::EndScene()
			{
			}

			void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
			{
				// Shader
				shader->Bind();
				shader->UploadUniformMat4("uViewProjection", sceneData->viewProjectionMatrix);

				shader->UploadUniformMat4("uTransform", transform);

				// VAO
				vertexArray->Bind();

				// Draw
				RenderCommand::Draw(vertexArray);
			}
		}
	}
}