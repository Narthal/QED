#include "enginePCH.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			void Renderer::BeginScene()
			{
			}

			void Renderer::EndScene()
			{
			}

			void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
			{
				vertexArray->Bind();
				RenderCommand::Draw(vertexArray);
			}
		}
	}
}