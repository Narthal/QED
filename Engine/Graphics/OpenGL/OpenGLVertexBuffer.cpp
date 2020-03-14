#include "EnginePCH.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
				{
					glCreateBuffers(1, &rendererID);
					glBindBuffer(GL_ARRAY_BUFFER, rendererID);
					glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
				}

				OpenGLVertexBuffer::~OpenGLVertexBuffer()
				{
					glDeleteBuffers(1, &rendererID);
				}

				void OpenGLVertexBuffer::Bind() const
				{
					glBindBuffer(GL_ARRAY_BUFFER, rendererID);
				}

				void OpenGLVertexBuffer::Unbind() const
				{
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

			}
		}
	}
}
