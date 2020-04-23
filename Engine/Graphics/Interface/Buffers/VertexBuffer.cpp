#include "EnginePCH.h"
#include "VertexBuffer.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/OpenGL/Buffers/OpenGLVertexBuffer.h"

#include "Profiler/Instrumentor.h"

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
					Ref<VertexBuffer> VertexBuffer::Create(UInt size)
					{
						QED_PROFILE_FUNCTION();

						switch (Renderer::Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Buffers::OpenGLVertexBuffer>(size);
							break;

							default:
							// TODO: crash here
							return nullptr;
							break;
						}

						// TODO: crash here
						return nullptr;
					}

					Ref<VertexBuffer> VertexBuffer::Create(float* vertices, UInt size)
					{
						QED_PROFILE_FUNCTION();

						switch (Renderer::Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Buffers::OpenGLVertexBuffer>(vertices, size);
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

