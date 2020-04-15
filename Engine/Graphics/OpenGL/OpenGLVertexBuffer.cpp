#include "EnginePCH.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

#include <Profiler/Instrumentor.h>

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
					QED_PROFILE_FUNCTION();

					glCreateBuffers(1, &rendererID);
					glBindBuffer(GL_ARRAY_BUFFER, rendererID);
					glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
				}

				OpenGLVertexBuffer::~OpenGLVertexBuffer()
				{
					QED_PROFILE_FUNCTION();

					glDeleteBuffers(1, &rendererID);
				}

				void OpenGLVertexBuffer::Bind() const
				{
					QED_PROFILE_FUNCTION();

					glBindBuffer(GL_ARRAY_BUFFER, rendererID);
				}

				void OpenGLVertexBuffer::Unbind() const
				{
					QED_PROFILE_FUNCTION();

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

			}
		}
	}
}
