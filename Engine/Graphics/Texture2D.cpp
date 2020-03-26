#include "enginePCH.h"
#include "Texture2D.h"

#include "Renderer.h"
#include "OpenGL/OpenGLTexture2D.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Ref<Texture2D> Texture2D::Create(const std::string& path)
			{
				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return std::make_shared<OpenGL::OpenGLTexture2D>(path);
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

