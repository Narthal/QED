#ifndef RENDERER_H
#define RENDERER_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

#include "Graphics/Interface/API/RendererAPI.h"
#include "Graphics/Interface/Buffers/VertexArray.h"
#include "Graphics/Camera/OrthographicCamera.h"
#include "Graphics/Interface/Shaders/Shader.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Renderer
			{
				class Renderer
				{
				public:
					static void Initialize();

				public:
					static void OnWindowResize(uint32_t width, uint32_t height);

				public:
					static void BeginScene(Camera::OrthographicCamera& camera);
					static void EndScene();
					static void Submit(const Ref<Interface::Shaders::Shader>& shader, const Ref<Interface::Buffers::VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

				public:
					inline static Interface::API::RendererAPI::API GetAPI() { return Interface::API::RendererAPI::GetAPI(); }

				private:
					struct SceneData
					{
						glm::mat4 viewProjectionMatrix;
					};
					static Scope<SceneData> sceneData;
				};
			}
		}
	}
}


#endif // !RENDERER_H
