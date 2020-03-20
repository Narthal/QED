#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "../RendererAPI.h"

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
					virtual void Clear() override;

					public:
					virtual void SetClearColor(const glm::vec4 color) override;

					public:
					virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) override;

				};
			}
		}
	}
}


#endif // !OPENGL_RENDERER_API_H