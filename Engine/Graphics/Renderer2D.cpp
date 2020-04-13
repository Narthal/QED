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
				Ref<Shader> FlatColorShader;
				Ref<Shader> TextureShader;
			};

			static Renderer2D_Data* renderer2D_Data;

			void Renderer2D::Initialize()
			{
				renderer2D_Data = new Renderer2D_Data();

				renderer2D_Data->VertexArray = VertexArray::Create();
				float vertices[(3 + 2) * 4] =
				{
					-0.5f, -0.5f,  0.0f,	0.0f, 0.0f,
					 0.5f, -0.5f,  0.0f,	1.0f, 0.0f,
					 0.5f,  0.5f,  0.0f,	1.0f, 1.0f,
					-0.5f,  0.5f,  0.0f,	0.0f, 1.0f,
				};

				Ref<VertexBuffer> vertexBuffer;
				vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
				vertexBuffer->SetLayout
				({
					{ ShaderDataType::Float3, "aPosition" },
					{ ShaderDataType::Float2, "aTextureCoordinate" }
				});
				renderer2D_Data->VertexArray->AddVertexBuffer(vertexBuffer);

				unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
				Ref<IndexBuffer> indexBuffer;
				indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
				renderer2D_Data->VertexArray->SetIndexBuffer(indexBuffer);

				renderer2D_Data->FlatColorShader = Shader::Create("FlatColor.glsl");
				renderer2D_Data->TextureShader = Shader::Create("Texture.glsl");
				renderer2D_Data->TextureShader->Bind();
				renderer2D_Data->TextureShader->SetInt("uTexture", 0);
			}

			void Renderer2D::ShutDown()
			{
				delete renderer2D_Data;
			}

			void Renderer2D::BeginScene(const OrthographicCamera& camera)
			{
				renderer2D_Data->FlatColorShader->Bind();
				renderer2D_Data->FlatColorShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

				renderer2D_Data->TextureShader->Bind();
				renderer2D_Data->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
			}

			void Renderer2D::EndScene()
			{
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				renderer2D_Data->FlatColorShader->Bind();
				renderer2D_Data->FlatColorShader->SetFloat4("uColor", color);

				glm::mat4 transform = glm::identity<glm::mat4>();
				transform = glm::translate(transform, position);
				transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
				transform = glm::scale(transform, { size.x, size.y, 1.0f });

				renderer2D_Data->FlatColorShader->SetMat4("uTransform", transform);

				renderer2D_Data->VertexArray->Bind();
				RenderCommand::Draw(renderer2D_Data->VertexArray);
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture)
			{
				renderer2D_Data->TextureShader->Bind();

				glm::mat4 transform = glm::identity<glm::mat4>();
				transform = glm::translate(transform, position);
				transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
				transform = glm::scale(transform, { size.x, size.y, 1.0f });

				renderer2D_Data->TextureShader->SetMat4("uTransform", transform);

				texture->Bind();

				renderer2D_Data->VertexArray->Bind();
				RenderCommand::Draw(renderer2D_Data->VertexArray);
			}
		}
	}
}

