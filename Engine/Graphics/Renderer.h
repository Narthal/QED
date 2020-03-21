#ifndef RENDERER_H
#define RENDERER_H

#include "../Module/QEDApi.h"

#include "RendererAPI.h"
#include "VertexArray.h"
#include "OrthographicCamera.h"
#include "Shader.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API Renderer
			{
			public:
				static void BeginScene(OrthographicCamera& camera);
				static void EndScene();
				static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

			public:
				inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

			private:
				struct SceneData
				{
					glm::mat4 viewProjectionMatrix;
				};
				static SceneData* sceneData;
			};
		}
	}
}


#endif // !RENDERER_H
