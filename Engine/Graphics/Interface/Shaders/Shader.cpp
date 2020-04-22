#include "EnginePCH.h"
#include "Shader.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/OpenGL/Shaders/OpenGLShader.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Shaders
				{
					Ref<Shader> Shader::Create(const std::string& path)
					{
						QED_PROFILE_FUNCTION();

						switch (Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Shaders::OpenGLShader>(path);
							break;

							default:
							// TODO: crash here
							return nullptr;
							break;
						}

						// TODO: crash here
						return nullptr;
					}

					Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
					{
						QED_PROFILE_FUNCTION();

						switch (Renderer::GetAPI())
						{
							case Interface::API::RendererAPI::API::NONE:
							// TODO: crash here
							return nullptr;
							break;

							case Interface::API::RendererAPI::API::OpenGL:
							return Core::Type::CreateRef<OpenGL::Shaders::OpenGLShader>(name, vertexSource, fragmentSource);
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