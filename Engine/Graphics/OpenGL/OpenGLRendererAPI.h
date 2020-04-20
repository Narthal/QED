#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "../RendererAPI.h"
#include "../Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLRendererAPI : public RendererAPI
				{
				public:
					virtual void Initialize() override;

				public:
					virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
					virtual void Clear() override;
					virtual void SetClearColor(const glm::vec4 color) override;
					virtual void Draw(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;

				};
			}
		}
	}
}


#endif // !OPENGL_RENDERER_API_H
