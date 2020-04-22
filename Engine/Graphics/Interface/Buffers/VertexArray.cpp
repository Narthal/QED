#include "enginePCH.h"
#include "VertexArray.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/OpenGL/Buffers/OpenGLVertexArray.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Ref<VertexArray> VertexArray::Create()
			{
				QED_PROFILE_FUNCTION();
				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return Core::Type::CreateRef<OpenGL::OpenGLVertexArray>();
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