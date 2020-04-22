#include "enginePCH.h"
#include "RenderCommand.h"

#include "Graphics/Interface/API/RendererAPI.h"
#include "Graphics/OpenGL/API/OpenGLRendererAPI.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			Ref<Interface::API::RendererAPI> RenderCommand::rendererAPI = Core::Type::CreateRef<OpenGL::API::OpenGLRendererAPI>();
		}
	}
}