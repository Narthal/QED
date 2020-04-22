#include "EnginePCH.h"
#include "OpenGLVertexBuffer.h"

// GLAD
#include <glad/glad.h>

#include "Profiler/Instrumentor.h"

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
					OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
					{
						QED_PROFILE_FUNCTION();

						glCreateBuffers(1, &rendererID);
						glBindBuffer(GL_ARRAY_BUFFER, rendererID);
						glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
					}

					OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
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

					void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
					{
						glBindBuffer(GL_ARRAY_BUFFER, rendererID);
						glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
					}
				}
			}
		}
	}
}
