#include "EnginePCH.h"
#include "IndexBuffer.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/OpenGL/Buffers/OpenGLIndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Buffers
				{
					Ref<IndexBuffer> IndexBuffer::Create(UInt* indices, UInt count)
					{
						switch (Renderer::Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Buffers::OpenGLIndexBuffer>(indices, count);
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
	}
}

