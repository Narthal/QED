#include "EnginePCH.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
			{
				switch (Renderer::GetAPI())
				{
					case RendererAPI::NONE:
					// TODO: crash here
					return nullptr;
					break;
					
					case RendererAPI::OpenGL:
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

