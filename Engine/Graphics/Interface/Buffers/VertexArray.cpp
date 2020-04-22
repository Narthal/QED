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
			namespace Interface
			{
				namespace Buffers
				{
					Ref<VertexArray> VertexArray::Create()
					{
						QED_PROFILE_FUNCTION();
						switch (Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Buffers::OpenGLVertexArray>();
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