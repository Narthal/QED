#include "EnginePCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				void OpenGLRendererAPI::Initialize()
				{
					// Enable blending (transparency)
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}

				void OpenGLRendererAPI::Clear()
				{
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				}

				void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
				{
					glClearColor(color.r, color.g, color.g, color.a);
				}

				void OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray)
				{
					glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
				}
			}
		}
	}
}

