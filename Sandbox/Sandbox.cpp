#include "sandboxPCH.h"

#include "QED.h"

namespace QED
{
	namespace Sandbox
	{
		class SandboxLayer : public Engine::Layer::Layer
		{
		public:
			// Construtor
			SandboxLayer() : Engine::Layer::Layer("SandboxLayer", true), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f)
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

				std::shared_ptr<Engine::Graphics::VertexBuffer> vertexBuffer;
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
				std::shared_ptr<Engine::Graphics::IndexBuffer> indexBuffer;
				indexBuffer.reset(Engine::Graphics::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
				vertexArray->SetIndexBuffer(indexBuffer);

				// square
				squareVA.reset(Engine::Graphics::VertexArray::Create());
				float squareVertices[3 * 4] =
				{
					-0.5f, -0.5f,  0.0f,
					 0.5f, -0.5f,  0.0f,
					 0.5f,  0.5f,  0.0f,
					-0.5f,  0.5f,  0.0f,
				};

				std::shared_ptr<Engine::Graphics::VertexBuffer> squareVB;
				squareVB.reset(Engine::Graphics::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
				squareVB->SetLayout
				({
					{ Engine::Graphics::ShaderDataType::Float3, "aPosition" },
				});
				squareVA->AddVertexBuffer(squareVB);

				unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
				std::shared_ptr<Engine::Graphics::IndexBuffer> squareIB;
				squareIB.reset(Engine::Graphics::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
				squareVA->SetIndexBuffer(squareIB);


				std::string squareVertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;

					uniform mat4 uViewProjection;

					out vec3 vPosition;

					void main()
					{
						vPosition = aPosition;

						gl_Position = uViewProjection * vec4(aPosition, 1.0);
					}
				)";

				std::string squareFragmentSource =
					R"(
					#version 330 core
					
					layout(location = 0) out vec4 color;

					in vec3 vPosition;

					void main()
					{
						color = vec4((vPosition + 1) / 2, 1.0);
					}
				)";

				std::string vertexSource =
					R"(
					#version 330 core
					
					layout(location = 0) in vec3 aPosition;
					layout(location = 1) in vec4 aColor;

					uniform mat4 uViewProjection;

					out vec3 vPosition;
					out vec4 vColor;

					void main()
					{
						vPosition = aPosition;
						vColor = aColor;

						gl_Position = uViewProjection * vec4(aPosition, 1.0);
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
			virtual void OnUpdate() override
			{
				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_A))
				{
					cameraPos.x -= cameraSpeed;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_D))
				{
					cameraPos.x += cameraSpeed;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_W))
				{
					cameraPos.y -= cameraSpeed;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_S))
				{
					cameraPos.y += cameraSpeed;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_Q))
				{
					cameraRot -= cameraRotSpeed;
				}

				if (Engine::Input::CoreInput::IsKeyPressed(Engine::Input::key_E))
				{
					cameraRot += cameraRotSpeed;
				}

				// Clear
				Engine::Graphics::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
				Engine::Graphics::RenderCommand::Clear();

				camera.SetPosition(cameraPos);
				camera.SetRotation(cameraRot);

				// Test
				Engine::Graphics::Renderer::BeginScene(camera);

				Engine::Graphics::Renderer::Submit(squareShader, squareVA);
				Engine::Graphics::Renderer::Submit(shader, vertexArray);

				Engine::Graphics::Renderer::EndScene();
			}

			// Override layer's OnUIRender method
			virtual void OnUIRender() override
			{
			}

			// Override layer's OnEvent method
			virtual void OnEvent(Engine::Event::Event& event) override
			{
			}

		private:
			std::shared_ptr<Engine::Graphics::VertexArray> vertexArray;
			std::shared_ptr<Engine::Graphics::Shader> shader;

			std::shared_ptr<Engine::Graphics::VertexArray> squareVA;
			std::shared_ptr<Engine::Graphics::Shader> squareShader;

			Engine::Graphics::OrthographicCamera camera;
			glm::vec3 cameraPos;
			float cameraSpeed = 0.1f;
			float cameraRot = 0.0f;
			float cameraRotSpeed = 2.0f;
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
