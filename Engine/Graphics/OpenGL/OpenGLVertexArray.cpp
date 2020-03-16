#include "EnginePCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				// TODO: move this func
				static GLenum ShdaderDataTypeToOpenGL(Graphics::ShaderDataType shaderDataType)
				{
					switch (shaderDataType)
					{
						// NONE
						case QED::Engine::Graphics::ShaderDataType::NONE:
						// TODO: crash here
						break;

						// Floats
						case QED::Engine::Graphics::ShaderDataType::Float:		return GL_FLOAT;
						case QED::Engine::Graphics::ShaderDataType::Float2:		return GL_FLOAT;
						case QED::Engine::Graphics::ShaderDataType::Float3:		return GL_FLOAT;
						case QED::Engine::Graphics::ShaderDataType::Float4:		return GL_FLOAT;

							// Matrices
						case QED::Engine::Graphics::ShaderDataType::Mat3:		return GL_FLOAT;
						case QED::Engine::Graphics::ShaderDataType::Mat4:		return GL_FLOAT;

							// Integers
						case QED::Engine::Graphics::ShaderDataType::Int:		return GL_INT;
						case QED::Engine::Graphics::ShaderDataType::Int2:		return GL_INT;
						case QED::Engine::Graphics::ShaderDataType::Int3:		return GL_INT;
						case QED::Engine::Graphics::ShaderDataType::Int4:		return GL_INT;

							// Boolean
						case QED::Engine::Graphics::ShaderDataType::Bool:		return GL_BOOL;

							// Default
						default:
						// TODO: crash here
						break;
					}

					// TODO: crash here
					return -1;
				}

				OpenGLVertexArray::OpenGLVertexArray()
				{
					glCreateVertexArrays(1, &rendererID);
				}

				OpenGLVertexArray::~OpenGLVertexArray()
				{
					glDeleteVertexArrays(1, &rendererID);
				}

				void OpenGLVertexArray::Bind() const
				{
					glBindVertexArray(rendererID);
				}

				void OpenGLVertexArray::Unbind() const
				{
					glBindVertexArray(0);
				}

				void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
				{
					glBindVertexArray(rendererID);
					vertexBuffer->Bind();

					// TODO: crash here
					// if vertexBuffer->GetLayout().size() must not be 0 "vertexBuffer has no layout"

					uint32_t index = 0;
					for (const auto& element : vertexBuffer->GetLayout())
					{
						glEnableVertexAttribArray(index);
						glVertexAttribPointer
						(
							index,
							element.GetComponentCount(),
							ShdaderDataTypeToOpenGL(element.shaderDataType),
							element.normalized ? GL_TRUE : GL_FALSE,
							vertexBuffer->GetLayout().GetStride(),
							(const void*)element.offset
						);
						index++;
					}

					vertexBuffers.push_back(vertexBuffer);
				}

				void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
				{
					glBindVertexArray(rendererID);
					indexBuffer->Bind();

					this->indexBuffer = indexBuffer;
				}
			}
		}
	}
}
