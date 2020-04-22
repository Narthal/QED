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
			Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
			{
				QED_PROFILE_FUNCTION();

				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return Core::Type::CreateRef<OpenGL::OpenGLVertexBuffer>(size);
					break;

					default:
					// TODO: crash here
					return nullptr;
					break;
				}

				// TODO: crash here
				return nullptr;
			}

			Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
			{
				QED_PROFILE_FUNCTION();

				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;
					
					case RendererAPI::API::OpenGL:
					return Core::Type::CreateRef<OpenGL::OpenGLVertexBuffer>(vertices, size);
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

