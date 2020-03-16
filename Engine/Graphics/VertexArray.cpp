#include "enginePCH.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "OpenGL/OpenGLVertexArray.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			VertexArray* VertexArray::Create()
			{
				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return new OpenGL::OpenGLVertexArray();
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