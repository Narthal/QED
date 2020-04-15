#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include "../VertexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLVertexBuffer : public VertexBuffer
				{
				public:
					OpenGLVertexBuffer(float* vertices, unsigned int size);

					virtual ~OpenGLVertexBuffer();

				public:
					virtual void Bind() const override;

					virtual void Unbind() const override;

				public:
					inline virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; };

					inline virtual const BufferLayout& GetLayout() const override { return layout; };

				private:
					BufferLayout layout;
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_VERTEX_BUFFER_H
