#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

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
					inline static void SetViewport(UInt x, UInt y, UInt width, UInt height) { rendererAPI->SetViewport(x, y, width, height); }
					inline static void SetClearColor(const Vec4& color) { rendererAPI->SetClearColor(color); }
					inline static void Clear() { rendererAPI->Clear(); }
					inline static void Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, UInt indexCount = 0) { rendererAPI->Draw(vertexArray, indexCount); }

				private:
					static Ref<Interface::API::RendererAPI> rendererAPI;
				};
			}
		}
	}
}


#endif // !RENDER_COMMAND_H
