#include "EnginePCH.h"
#include "Renderer2D.h"

#include "Core/Type/Type.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <Profiler/Instrumentor.h>

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
				Ref<Texture2D> Texture;
			};

			static Renderer2D_Data* renderer2D_Data;

			void Renderer2D::Initialize()
			{
				QED_PROFILE_FUNCTION();

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

				renderer2D_Data->Texture = Texture2D::Create(1, 1);
				uint32_t whiteTextureData = 0xffffffff;
				renderer2D_Data->Texture->SetData(&whiteTextureData, sizeof(uint32_t));

				renderer2D_Data->Shader = Shader::Create("Renderer2D.glsl");
				renderer2D_Data->Shader->Bind();
				renderer2D_Data->Shader->SetInt("uTexture", 0);
			}

			void Renderer2D::ShutDown()
			{
				QED_PROFILE_FUNCTION();

				delete renderer2D_Data;
			}

			void Renderer2D::BeginScene(const OrthographicCamera& camera)
			{
				QED_PROFILE_FUNCTION();
				renderer2D_Data->Shader->Bind();
				renderer2D_Data->Shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
			}

			void Renderer2D::EndScene()
			{
				
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, renderer2D_Data->Texture, color);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				DrawQuad(position, size, rotation, renderer2D_Data->Texture, color);
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture, float tilingFactor)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, glm::vec4(1.0f), tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture, float tilingFactor)
			{
				DrawQuad(position, size, rotation, texture, glm::vec4(1.0f), tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture, const glm::vec4& color, float tilingFactor)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, color, tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Texture2D>& texture, const glm::vec4& color, float tilingFactor)
			{
				QED_PROFILE_FUNCTION();
				// Set color uniform
				renderer2D_Data->Shader->SetFloat4("uColor", color);

				// Set tiling factor uniform
				renderer2D_Data->Shader->SetFloat("uTilingFactor", tilingFactor);

				// Bind texture
				texture->Bind();

				// Calculate transform
				glm::mat4 transform = glm::identity<glm::mat4>();
				transform = glm::translate(transform, position);
				transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
				transform = glm::scale(transform, { size.x, size.y, 1.0f });

				// Set transform uniform
				renderer2D_Data->Shader->SetMat4("uTransform", transform);

				// Draw
				renderer2D_Data->VertexArray->Bind();
				RenderCommand::Draw(renderer2D_Data->VertexArray);
			}
		}
	}
}

