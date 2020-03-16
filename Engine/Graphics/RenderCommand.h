#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Renderer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class RenderCommand
			{
				public:
				inline static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }

				public:
				inline static void Clear() { rendererAPI->Clear(); }

				public:
				inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
				{
					rendererAPI->Draw(vertexArray);
				}

				private:
				static RendererAPI* rendererAPI;
			};
		}
	}
}


#endif // !RENDER_COMMAND_H
