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
			Ref<RendererAPI> RenderCommand::rendererAPI = Core::Type::CreateRef<OpenGL::OpenGLRendererAPI>();
		}
	}
}