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
					virtual void Bind() const;

					public:
					virtual void Unbind() const;

					private:
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_VERTEX_BUFFER_H
