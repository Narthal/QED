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
			Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int size)
			{
				switch (Renderer::Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return Core::Type::CreateRef<OpenGL::OpenGLIndexBuffer>(indices, size);
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

