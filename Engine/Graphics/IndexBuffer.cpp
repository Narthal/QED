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
			Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
			{
				switch (Renderer::Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return Core::Type::CreateRef<OpenGL::OpenGLIndexBuffer>(indices, count);
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

