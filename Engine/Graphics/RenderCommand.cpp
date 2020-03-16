#include "enginePCH.h"
#include "RenderCommand.h"

#include "RendererAPI.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			RendererAPI* RenderCommand::rendererAPI = new OpenGL::OpenGLRendererAPI;
		}
	}
}