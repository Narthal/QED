#include "EnginePCH.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
			{
				switch (Renderer::Renderer::GetAPI())
				{
					case RendererAPI::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::OpenGL:
					return new OpenGL::OpenGLIndexBuffer(indices, size);
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

