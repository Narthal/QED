#include "EnginePCH.h"
#include "RenderCommandInterface.h"

#include "RenderCommand.h"

namespace QED
{
	namespace Interface
	{
		namespace Graphics
		{
			namespace Renderer
			{
				void RenderCommand::SetClearColor(const Vec4& color) { Engine::Graphics::Renderer::RenderCommand::SetClearColor(color); }
				void RenderCommand::Clear() { Engine::Graphics::Renderer::RenderCommand::Clear(); }
			}
		}
	}
}