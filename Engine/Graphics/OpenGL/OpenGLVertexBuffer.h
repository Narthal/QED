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

					public:
					virtual ~OpenGLVertexBuffer();

					public:
					virtual void Bind() const override;

					public:
					virtual void Unbind() const override;

					private:
					unsigned int rendererID;

					public:
					inline virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; };

					public:
					inline virtual const BufferLayout& GetLayout() const override { return layout; };

					private:
					BufferLayout layout;
				};
			}
		}
	}
}

#endif // !OPENGL_VERTEX_BUFFER_H
