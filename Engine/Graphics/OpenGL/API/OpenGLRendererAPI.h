#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "Core/Type/Type.h"

#include "Graphics/Interface/API/RendererAPI.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace API
				{
					class OpenGLRendererAPI : public Interface::API::RendererAPI
					{
					public:
						virtual void Initialize() override;

					public:
						virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
						virtual void Clear() override;
						virtual void SetClearColor(const glm::vec4 color) override;
						virtual void Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, uint32_t indexCount) override;
					};
				}
			}
		}
	}
}


#endif // !OPENGL_RENDERER_API_H
