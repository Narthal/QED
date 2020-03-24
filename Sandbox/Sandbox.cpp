#include "sandboxPCH.h"

#include "QED.h"

// TODO: move this
#include <glm\ext\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace QED
{
	namespace Sandbox
	{
		class SandboxLayer : public Engine::Layer::Layer
		{
		public:
			// Construtor
			SandboxLayer() : Engine::Layer::Layer("SandboxLayer", true), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f), squarePosition(0.0f)
			{
				LOG << "Sandbox layer ctor";

				// Test
				vertexArray.reset(Engine::Graphics::VertexArray::Create());

				float vertices[3 * (3 + 4)] =
				{
					-0.5f, -0.5f,  0.0f,	1.0f, 0.0f,  1.0f, 1.0f,
					 0.5f, -0.5f,  0.0f,	0.0f, 1.0f,  1.0f, 1.0f,
					 0.0f,  0.5f,  0.0f,	1.0f, 1.0f,  0.0f, 1.0f,
				};

				Ref<Engine::Graphics::VertexBuffer> vertexBuffer;
				vertexBuffer.reset(Engine::Graphics::VertexBuffer::Create(vertices, sizeof(vertices)));

				{
					Engine::Graphics::BufferLayout layout =
					{
						{ Engine::Graphics::ShaderDataType::Float3, "aPosition" },
						{ Engine::Graphics::ShaderDataType::Float4, "aColor" },
					};

					vertexBuffer->SetLayout(layout);
				}

				vertexArray->AddVertexBuffer(vertexBuffer);

				unsigned int indices[3] = { 0, 1, 2 };
				Ref<Engine::Graphics::IndexBuffer> indexBuffer;
				indexBuffer.reset(Engine::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
				vertexArray->SetIndexBuffer(indexBuffer);

				// square
				squareVA.reset(Engine::Graphics::VertexArray::Create());
				float squareVertices[(3 + 2) * 4] =
				{
					-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
					 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
					 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
					-0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
				};

				Ref<Engine::Graphics::VertexBuffer> squareVB;
				squareVB.reset(Engine::Graphics::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
				squareVB->SetLayout
				({
					{ Engine::Graphics::ShaderDataType::Float3, "aPosition" },
					{ Engine::Graphics::ShaderDataType::Float2, "aTextureCoordinate" },
				});
				squareVA->AddVertexBuffer(squareVB);

				unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
				Ref<Engine::Graphics::IndexBuffer> squareIB;
				squareIB.reset(Engine::Graphics::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
				squareVA->SetIndexBuffer(squareIB);


				std::string squareVertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;

					uniform mat4 uViewProjection;
					uniform mat4 uTransform;

					out vec3 vPosition;

					void main()
					{
						vPosition = aPosition;

						gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
					}
				)";

				std::string squareFragmentSource =
					R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;

					uniform vec3 uColor;

					void main()
					{
						//color = vec4((vPosition + 1) / 2, 1.0);
						color = vec4(uColor, 1.0f);
					}
				)";

				std::string textureVertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;
					layout(location = 1) in vec2 aTextureCoordinate;

					uniform mat4 uViewProjection;
					uniform mat4 uTransform;

					out vec3 vPosition;
					out vec2 vTextureCoordinate;

					void main()
					{
						vPosition = aPosition;
						vTextureCoordinate = aTextureCoordinate;
						gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
					}
				)";

				std::string textureFragmentSource =
					R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;
					in vec2 vTextureCoordinate;

					uniform sampler2D uTexture;

					void main()
					{
						color = texture(uTexture, vTextureCoordinate);
					}
				)";

				std::string vertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;
					layout(location = 1) in vec4 aColor;

					uniform mat4 uViewProjection;
					uniform mat4 uTransform;

					out vec3 vPosition;
					out vec4 vColor;

					void main()
					{
						vPosition = aPosition;
						vColor = aColor;

						gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
					}
				)";

				std::string fragmentSource =
					R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;
					in vec4 vColor;

					void main()
					{
						color = vec4((vPosition + 1) / 2, 1.0);
						color = vColor;
					}
				)";

				shader.reset(Engine::Graphics::Shader::Create(vertexSource, fragmentSource));
				squareShader.reset(Engine::Graphics::Shader::Create(squareVertexSource, squareFragmentSource));
				textureShader.reset(Engine::Graphics::Shader::Create(textureVertexSource, textureFragmentSource));

				texture = Engine::Graphics::Texture2D::Create("missingTexture.png");
				textureShader->Bind();
				textureShader->UploadUniformInt("uTexture", 0);
			}

			// Override inherited pure virtual destructor
			virtual ~SandboxLayer() override
			{
				LOG << "Sandbox layer dtor";
			};

			// Get name for module interface
			QED_MODULE_API virtual const char* GetName() const override
			{
				return "SandboxLayer";
			}

			// Override layer's OnUpdate method
			virtual void OnUpdate(Engine::Core::Time::TimeStep timeStep) override
			{
				LOG << "Delta time : " << timeStep.GetSeconds();

				// Move camera

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_A))
				{
					cameraPos.x -= cameraSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_D))
				{
					cameraPos.x += cameraSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_W))
				{
					cameraPos.y += cameraSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_S))
				{
					cameraPos.y -= cameraSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_Q))
				{
					cameraRot -= cameraRotSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_E))
				{
					cameraRot += cameraRotSpeed * timeStep;
				}

				// Move square

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_LEFT))
				{
					squarePosition.x -= squareSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_RIGHT))
				{
					squarePosition.x += squareSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_UP))
				{
					squarePosition.y += squareSpeed * timeStep;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_DOWN))
				{
					squarePosition.y -= squareSpeed * timeStep;
				}

				// Clear
				Engine::Graphics::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
				Engine::Graphics::RenderCommand::Clear();

				camera.SetPosition(cameraPos);
				camera.SetRotation(cameraRot);

				// Test
				Engine::Graphics::Renderer::BeginScene(camera);

				squareShader->Bind();
				squareShader->UploadUniformFloat3("uColor", squareColor);

				glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f));

				glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
				glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
				for (size_t i = 0; i < 10; i++)
				{
					for (size_t j = 0; j < 10; j++)
					{
						glm::vec3 pos(i * 0.1f, j * 0.1f, 0.0f);
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + squarePosition) * scale;
						Engine::Graphics::Renderer::Submit(squareShader, squareVA, transform);
					}
				}

				texture->Bind();

				Engine::Graphics::Renderer::Submit(textureShader, squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.2f)));

				// Triangle
				//Engine::Graphics::Renderer::Submit(shader, vertexArray);

				Engine::Graphics::Renderer::EndScene();
			}

			// Override layer's OnUIRender method
			virtual void OnUIRender() override
			{
				ImGui::Begin("Settings");
				ImGui::ColorEdit3("Square color", glm::value_ptr(squareColor));
				ImGui::End();
			}

			// Override layer's OnEvent method
			virtual void OnEvent(Engine::Event::Event& event) override
			{
			}

		private:
			Ref<Engine::Graphics::VertexArray> vertexArray;
			Ref<Engine::Graphics::Shader> shader;

			Ref<Engine::Graphics::VertexArray> squareVA;
			Ref<Engine::Graphics::Shader> squareShader;

			Ref<Engine::Graphics::Shader> textureShader;

			Ref<Engine::Graphics::Texture2D> texture;

			Engine::Graphics::OrthographicCamera camera;
			glm::vec3 cameraPos;
			float cameraSpeed = 5.0f;
			float cameraRot = 0.0f;
			float cameraRotSpeed = 20.0f;

			float squareSpeed = 5.0f;
			glm::vec3 squarePosition;

			glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };
		};
	}
}



// Register the module to the engine kernel
extern "C" QED_MODULE_API void Register(QED::Engine::Module::Module& module)
{
	// Set module name
	module.moduleName = "Sandbox";

	// Send back interface instances
	QED::Sandbox::SandboxLayer* sandboxLayer = new QED::Sandbox::SandboxLayer();
	sandboxLayer->Initialize();
	module.interfaces.emplace_back((QED::Engine::Module::Interfaces::ModuleInterface*)sandboxLayer);
}
