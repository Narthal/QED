#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Core/Type/Type.h"

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Interface/Buffers/VertexArray.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Renderer
			{
				class RenderCommand
				{
				public:
					inline static void Initialize() { QED_PROFILE_FUNCTION(); rendererAPI->Initialize(); }

				public:
					inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { rendererAPI->SetViewport(x, y, width, height); }
					inline static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
					inline static void Clear() { rendererAPI->Clear(); }
					inline static void Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, uint32_t indexCount = 0) { rendererAPI->Draw(vertexArray, indexCount); }

				private:
					static Ref<Interface::API::RendererAPI> rendererAPI;
				};
			}
		}
	}
}


#endif // !RENDER_COMMAND_H
