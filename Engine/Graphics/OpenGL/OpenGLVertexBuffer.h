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
					OpenGLVertexBuffer(uint32_t size);
					OpenGLVertexBuffer(float* vertices, uint32_t size);
					virtual ~OpenGLVertexBuffer();

				public:
					virtual void Bind() const override;
					virtual void Unbind() const override;

				public:
					inline virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; };
					inline virtual const BufferLayout& GetLayout() const override { return layout; };

					virtual void SetData(const void* data, uint32_t size) override;

				private:
					BufferLayout layout;
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_VERTEX_BUFFER_H
