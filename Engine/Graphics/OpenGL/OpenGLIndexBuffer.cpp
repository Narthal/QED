#include "EnginePCH.h"
#include "OpenGLIndexBuffer.h"

// OpenGL
#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count(count)
				{
					glCreateBuffers(1, &rendererID);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
				}

				OpenGLIndexBuffer::~OpenGLIndexBuffer()
				{
					glDeleteBuffers(1, &rendererID);
				}

				void OpenGLIndexBuffer::Bind() const
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
				}

				void OpenGLIndexBuffer::Unbind() const
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				}
			}
		}
	}
}

