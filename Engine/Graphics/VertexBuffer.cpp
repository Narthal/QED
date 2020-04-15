#include "EnginePCH.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

#include <Profiler/Instrumentor.h>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
			{
				QED_PROFILE_FUNCTION();

				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;
					
					case RendererAPI::API::OpenGL:
					return new OpenGL::OpenGLVertexBuffer(vertices, size);
					break;
					
					default:
					// TODO: crash here
					return nullptr;
					break;
				}

				// TODO: crash here
				return nullptr;
			}
		}
	}
}

