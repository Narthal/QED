#include "EnginePCH.h"
#include "Renderer2D.h"

#include "Core/Type/Type.h"

#include "RenderCommand.h"

#include "Graphics/Interface/Buffers/VertexArray.h"
#include "Graphics/Interface/Shaders/Shader.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			struct QuadVertex
			{
				glm::vec3 position;
				glm::vec4 color;
				glm::vec2 textureCoordinate;
				float textureIndex;
				float tilingFactor;
			};

			struct Renderer2DData
			{
				static const uint32_t maxQuads = 10000;
				static const uint32_t maxVertices = maxQuads * 4;
				static const uint32_t maxIndices = maxQuads * 6;
				static const uint32_t maxTextureSlots = 32;	// TODO: get from graphics driver

				Ref<Interface::Buffers::VertexArray> quadVertexArray;
				Ref<Interface::Buffers::VertexBuffer> quadVertexBuffer;

				Ref<Interface::Shaders::Shader> shader;
				Ref<Interface::Textures::Texture2D> whiteTexture;

				uint32_t quadIndexCount = 0;
				QuadVertex* quadVertexBufferBase = nullptr;
				QuadVertex* quadVertexBufferPtr = nullptr;

				std::array<Ref<Interface::Textures::Texture2D>, maxTextureSlots> textureSlots;
				uint32_t textureSlotIndex = 1;	// NOTE: 0 is a white texture

				glm::vec4 quadVertexPositions[4];

				Renderer2D::Statistics statistics;
			};

			static Renderer2DData renderer2DData;

			void Renderer2D::Initialize()
			{
				QED_PROFILE_FUNCTION();

				renderer2DData.quadVertexArray = Interface::Buffers::VertexArray::Create();

				renderer2DData.quadVertexBuffer = Interface::Buffers::VertexBuffer::Create(renderer2DData.maxVertices * sizeof(QuadVertex));
				renderer2DData.quadVertexBuffer->SetLayout
				({
					{ Interface::Buffers::ShaderDataType::Float3, "aPosition" },
					{ Interface::Buffers::ShaderDataType::Float4, "aColor" },
					{ Interface::Buffers::ShaderDataType::Float2, "aTextureCoordinate" },
					{ Interface::Buffers::ShaderDataType::Float, "aTextureIndex" },
					{ Interface::Buffers::ShaderDataType::Float, "aTilingFactor" }
				});
				renderer2DData.quadVertexArray->AddVertexBuffer(renderer2DData.quadVertexBuffer);

				renderer2DData.quadVertexBufferBase = new QuadVertex[renderer2DData.maxVertices];

				uint32_t* quadIndices = new uint32_t[renderer2DData.maxIndices];
				uint32_t offset = 0;
				for (uint32_t i = 0; i < renderer2DData.maxIndices; i += 6)
				{
					quadIndices[i + 0] = offset + 0;
					quadIndices[i + 1] = offset + 1;
					quadIndices[i + 2] = offset + 2;

					quadIndices[i + 3] = offset + 2;
					quadIndices[i + 4] = offset + 3;
					quadIndices[i + 5] = offset + 0;

					offset += 4;
				}
				Ref<Interface::Buffers::IndexBuffer> quadIndexBuffer = Interface::Buffers::IndexBuffer::Create(quadIndices, renderer2DData.maxIndices);
				renderer2DData.quadVertexArray->SetIndexBuffer(quadIndexBuffer);
				delete[] quadIndices;

				renderer2DData.whiteTexture = Interface::Textures::Texture2D::Create(1, 1);
				uint32_t whiteTextureData = 0xffffffff;
				renderer2DData.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

				uint32_t samplers[renderer2DData.maxTextureSlots];
				for (uint32_t i = 0; i < renderer2DData.maxTextureSlots; i++)
				{
					samplers[i] = i;
				}

				renderer2DData.shader = Interface::Shaders::Shader::Create("Renderer2D.glsl");
				renderer2DData.shader->Bind();
				renderer2DData.shader->SetIntArray("uTexture", samplers, renderer2DData.maxTextureSlots);

				// Set first texture slot to white texture
				renderer2DData.textureSlots[0] = renderer2DData.whiteTexture;

				renderer2DData.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
				renderer2DData.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
				renderer2DData.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
				renderer2DData.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
			}

			void Renderer2D::ShutDown()
			{
				QED_PROFILE_FUNCTION();
			}

			void Renderer2D::BeginScene(const Camera::OrthographicCamera& camera)
			{
				QED_PROFILE_FUNCTION();

				renderer2DData.shader->Bind();
				renderer2DData.shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
			
				renderer2DData.quadIndexCount = 0;
				renderer2DData.quadVertexBufferPtr = renderer2DData.quadVertexBufferBase;

				renderer2DData.textureSlotIndex = 1;
			}

			void Renderer2D::EndScene()
			{
				QED_PROFILE_FUNCTION();

				uint32_t dataSize = (uint8_t*)renderer2DData.quadVertexBufferPtr - (uint8_t*)renderer2DData.quadVertexBufferBase;
				renderer2DData.quadVertexBuffer->SetData(renderer2DData.quadVertexBufferBase, dataSize);

				Flush();
			}

			void Renderer2D::Flush()
			{
				QED_PROFILE_FUNCTION();

				for (uint32_t i = 0; i < renderer2DData.textureSlotIndex; i++)
				{
					renderer2DData.textureSlots[i]->Bind(i);
				}

				RenderCommand::Draw(renderer2DData.quadVertexArray, renderer2DData.quadIndexCount);

				// Statistics
				renderer2DData.statistics.drawCalls++;
			}

			void Renderer2D::FlushAndReset()
			{
				QED_PROFILE_FUNCTION();

				EndScene();

				renderer2DData.quadIndexCount = 0;
				renderer2DData.quadVertexBufferPtr = renderer2DData.quadVertexBufferBase;

				renderer2DData.textureSlotIndex = 1;
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, renderer2DData.whiteTexture, color);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color)
			{
				DrawQuad(position, size, rotation, renderer2DData.whiteTexture, color);
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, glm::vec4(1.0f), tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor)
			{
				DrawQuad(position, size, rotation, texture, glm::vec4(1.0f), tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const glm::vec4& color, float tilingFactor)
			{
				DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, color, tilingFactor);
			}

			void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const glm::vec4& color, float tilingFactor)
			{
				QED_PROFILE_FUNCTION();

				if (renderer2DData.quadIndexCount >= Renderer2DData::maxIndices)
				{
					FlushAndReset();
				}

				// Local texture index
				float textureIndex = 0.0f;

				if (texture != renderer2DData.whiteTexture)
				{
					// See if texture slots contain texture, and if so, set texture index to it
					for (uint32_t i = 1; i < renderer2DData.textureSlotIndex; i++)
					{
						if (ObjectEquals(renderer2DData.textureSlots[i], texture))
						{
							textureIndex = (float)i;
							break;
						}
					}

					// If texture is not in texture slots, set it to a texture slot
					if (textureIndex == 0.0f)
					{
						textureIndex = (float)renderer2DData.textureSlotIndex;
						renderer2DData.textureSlots[renderer2DData.textureSlotIndex] = texture;
						renderer2DData.textureSlotIndex++;
					}
				}

				// Calculate transform
				glm::mat4 transform = glm::identity<glm::mat4>();
				transform = glm::translate(transform, position);
				if (rotation != 0.0f) transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
				transform = glm::scale(transform, { size.x, size.y, 1.0f });

				renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[0];
				renderer2DData.quadVertexBufferPtr->color = color;
				renderer2DData.quadVertexBufferPtr->textureCoordinate = { 0.0f, 0.0f };
				renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
				renderer2DData.quadVertexBufferPtr->tilingFactor = tilingFactor;
				renderer2DData.quadVertexBufferPtr++;

				renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[1];
				renderer2DData.quadVertexBufferPtr->color = color;
				renderer2DData.quadVertexBufferPtr->textureCoordinate = { 1.0f, 0.0f };
				renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
				renderer2DData.quadVertexBufferPtr->tilingFactor = tilingFactor;
				renderer2DData.quadVertexBufferPtr++;

				renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[2];
				renderer2DData.quadVertexBufferPtr->color = color;
				renderer2DData.quadVertexBufferPtr->textureCoordinate = { 1.0f, 1.0f };
				renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
				renderer2DData.quadVertexBufferPtr->tilingFactor = tilingFactor;
				renderer2DData.quadVertexBufferPtr++;

				renderer2DData.quadVertexBufferPtr->position = transform * renderer2DData.quadVertexPositions[3];
				renderer2DData.quadVertexBufferPtr->color = color;
				renderer2DData.quadVertexBufferPtr->textureCoordinate = { 0.0f, 1.0f };
				renderer2DData.quadVertexBufferPtr->textureIndex = textureIndex;
				renderer2DData.quadVertexBufferPtr->tilingFactor = tilingFactor;
				renderer2DData.quadVertexBufferPtr++;

				renderer2DData.quadIndexCount += 6;

				// Statistics
				renderer2DData.statistics.quadCount++;
			}
			
			void Renderer2D::ResetStatistics()
			{
				memset(&renderer2DData.statistics, 0, sizeof(Statistics));
			}
			
			Renderer2D::Statistics Renderer2D::GetStatistics()
			{
				return renderer2DData.statistics;
			}
		}
	}
}

