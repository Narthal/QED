#include "EnginePCH.h"
#include "Renderer2D.h"

#include "Core/Type/Type.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			struct Renderer2D_Data
			{
				Ref<VertexArray> VertexArray;
				Ref<Shader> Shader;
			};

			static Renderer2D_Data* renderer2D_Data;

			void Renderer2D::Initialize()
			{
				renderer2D_Data = new Renderer2D_Data();

				renderer2D_Data->VertexArray = VertexArray::Create();
				float vertices[3 * 4] =
				{
					-0.5f, -0.5f,  0.0f,
					 0.5f, -0.5f,  0.0f,
					 0.5f,  0.5f,  0.0f,
					-0.5f,  0.5f,  0.0f,
				};

				Ref<VertexBuffer> vertexBuffer;
				vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
				vertexBuffer->SetLayout
				({
					{ ShaderDataType::Float3, "aPosition" }
				});
				renderer2D_Data->VertexArray->AddVertexBuffer(vertexBuffer);

				unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
				Ref<IndexBuffer> indexBuffer;
				indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
				renderer2D_Data->VertexArray->SetIndexBuffer(indexBuffer);

				renderer2D_Data->Shader = Shader::Create("FlatColor.glsl");
			}

			void Renderer2D::ShutDown()
			{
				delete renderer2D_Data;
			}

			void Renderer2D::BeginScene(const OrthographicCamera& camera)
			{
				renderer2D_Data->Shader->Bind();
				renderer2D_Data->Shader->UploadUniformMat4("uViewProjection", camera.GetViewProjectionMatrix());
				renderer2D_Data->Shader->UploadUniformMat4("uTransform", glm::mat4(1.0f));
			}

			void Renderer2D::EndScene()
			{
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, color);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
			{
				renderer2D_Data->Shader->Bind();
				renderer2D_Data->Shader->UploadUniformFloat4("uColor", color);

				renderer2D_Data->VertexArray->Bind();
				RenderCommand::Draw(renderer2D_Data->VertexArray);
			}

		}
	}
}

