#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "../Module/QEDApi.h"
#include "../Core/Type/Type.h"

#include "Renderer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API RenderCommand
			{
			public:
				inline static void Initialize() { rendererAPI->Initialize(); }

			public:
				inline static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
				inline static void Clear() { rendererAPI->Clear(); }
				inline static void Draw(const Ref<VertexArray>& vertexArray) { rendererAPI->Draw(vertexArray); }

			private:
				static RendererAPI* rendererAPI;
			};
		}
	}
}


#endif // !RENDER_COMMAND_H
