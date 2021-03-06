#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include "Graphics/Interface/Buffers/VertexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace Buffers
				{
					class OpenGLVertexBuffer : public Interface::Buffers::VertexBuffer
					{
					public:
						OpenGLVertexBuffer(UInt size);
						OpenGLVertexBuffer(float* vertices, UInt size);
						virtual ~OpenGLVertexBuffer();

					public:
						virtual void Bind() const override;
						virtual void Unbind() const override;

					public:
						inline virtual void SetLayout(const Interface::Buffers::BufferLayout& layout) override { this->layout = layout; };
						inline virtual const Interface::Buffers::BufferLayout& GetLayout() const override { return layout; };

						virtual void SetData(const void* data, UInt size) override;

					private:
						Interface::Buffers::BufferLayout layout;
						unsigned int rendererID;
					};
				}
			}
		}
	}
}

#endif // !OPENGL_VERTEX_BUFFER_H
