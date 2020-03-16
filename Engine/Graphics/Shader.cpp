#include "EnginePCH.h"
#include "Shader.h"

#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
			{
				switch (Renderer::GetAPI())
				{
					case RendererAPI::API::NONE:
					// TODO: crash here
					return nullptr;
					break;

					case RendererAPI::API::OpenGL:
					return new OpenGL::OpenGLShader(vertexSource, fragmentSource);
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