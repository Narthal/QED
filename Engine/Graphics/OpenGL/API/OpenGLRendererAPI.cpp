#include "EnginePCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace API
				{
					void OpenGLRendererAPI::Initialize()
					{
						QED_PROFILE_FUNCTION();

						// Enable blending (transparency)
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

						// Enable depth testing (for overlapping quads with different depth (x order))
						glEnable(GL_DEPTH_TEST);
					}

					void OpenGLRendererAPI::SetViewport(UInt x, UInt y, UInt width, UInt height)
					{
						glViewport(x, y, width, height);
					}

					void OpenGLRendererAPI::Clear()
					{
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					}

					void OpenGLRendererAPI::SetClearColor(const Vec4 color)
					{
						glClearColor(color.r, color.g, color.g, color.a);
					}

					void OpenGLRendererAPI::Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, UInt indexCount)
					{
						UInt count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
						glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
					}
				}
			}
		}
	}
}

