#ifndef RENDERER_H
#define RENDERER_H

#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

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
					static void OnWindowResize(UInt width, UInt height);

				public:
					static void BeginScene(Camera::OrthographicCamera& camera);
					static void EndScene();
					static void Submit(const Ref<Interface::Shaders::Shader>& shader, const Ref<Interface::Buffers::VertexArray>& vertexArray, const Mat4& transform = Mat4(1.0f));

				public:
					inline static Interface::API::RendererAPI::API GetAPI() { return Interface::API::RendererAPI::GetAPI(); }

				private:
					struct SceneData
					{
						Mat4 viewProjectionMatrix;
					};
					static Scope<SceneData> sceneData;
				};
			}
		}
	}
}


#endif // !RENDERER_H
