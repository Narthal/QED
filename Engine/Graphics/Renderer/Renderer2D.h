#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "Module/QEDApi.h"

#include "Graphics/Camera/OrthographicCamera.h"
#include "Graphics/Interface/Textures/Texture2D.h"

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
				static void BeginScene(const Camera::OrthographicCamera& camera);
				static void EndScene();
				static void Flush();

			private: // Internal
				static void FlushAndReset();

			public: // Primitives
				static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color);
				static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const glm::vec4& color);
				static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor = 1.0f);
				static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor = 1.0f);
				static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const glm::vec4& color, float tilingFactor = 1.0f);
				static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const glm::vec4& color, float tilingFactor = 1.0f);

			public: // Debug & Profiler structs
				struct Statistics
				{
					uint32_t drawCalls = 0;
					uint32_t quadCount = 0;

					uint32_t GetTotalVertexCount() { return quadCount * 4; }
					uint32_t GetTotalIndexCount() { return quadCount * 6; }
				};

			public:	// Debug & Profile
				static void ResetStatistics();
				static Statistics GetStatistics();
			};
		}
	}
}

#endif // !RENDERER_2D_H
