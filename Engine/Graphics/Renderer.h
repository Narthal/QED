#ifndef RENDERER_H
#define RENDERER_H

#include "RendererAPI.h"
#include "VertexArray.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class Renderer
			{
				public:
				static void BeginScene();

				public:
				static void EndScene();

				public:
				static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

				public:
				inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
			};
		}
	}
}


#endif // !RENDERER_H
