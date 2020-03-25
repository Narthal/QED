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
					virtual void Clear() override;
					virtual void SetClearColor(const glm::vec4 color) override;
					virtual void Draw(const Ref<VertexArray>& vertexArray) override;

				};
			}
		}
	}
}


#endif // !OPENGL_RENDERER_API_H
