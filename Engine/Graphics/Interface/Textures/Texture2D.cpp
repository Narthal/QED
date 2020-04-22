#include "enginePCH.h"
#include "Texture2D.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/OpenGL/Textures/OpenGLTexture2D.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Textures
				{
					Ref<Texture2D> Texture2D::Create(const std::string& path)
					{
						switch (Renderer::Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Textures::OpenGLTexture2D>(path);
							break;

							default:
							// TODO: crash here
							return nullptr;
							break;
						}

						// TODO: crash here
						return nullptr;
					}

					Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
					{
						switch (Renderer::Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Textures::OpenGLTexture2D>(width, height);
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


