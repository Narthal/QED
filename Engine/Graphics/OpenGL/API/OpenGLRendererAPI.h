#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "Core/Type/Reference.h"

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
						virtual void SetViewport(UInt x, UInt y, UInt width, UInt height) override;
						virtual void Clear() override;
						virtual void SetClearColor(const Vec4 color) override;
						virtual void Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, UInt indexCount) override;
					};
				}
			}
		}
	}
}


#endif // !OPENGL_RENDERER_API_H
