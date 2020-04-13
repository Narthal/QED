#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "Module/QEDApi.h"

#include "OrthographicCamera.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API Renderer2D
			{
			public: // Init & destroy
				static void Initialize();
				static void ShutDown();

			public: // Scene commands
				static void BeginScene(const OrthographicCamera& camera);
				static void EndScene();

			public: // Primitives
				static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color);
				static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color);
			};
		}
	}
}

#endif // !RENDERER_2D_H
