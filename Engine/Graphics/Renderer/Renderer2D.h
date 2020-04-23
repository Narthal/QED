#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "Module/QEDApi.h"

#include "Core/Type/Numeric.h"

#include "Graphics/Camera/OrthographicCamera.h"
#include "Graphics/Interface/Textures/Texture2D.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Renderer
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
					static void DrawQuad(const Vec2& position, const Vec2& size, const glm::float32 rotation, const Vec4& color);
					static void DrawQuad(const Vec3& position, const Vec2& size, const glm::float32 rotation, const Vec4& color);
					static void DrawQuad(const Vec2& position, const Vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor = 1.0f);
					static void DrawQuad(const Vec3& position, const Vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, float tilingFactor = 1.0f);
					static void DrawQuad(const Vec2& position, const Vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const Vec4& color, float tilingFactor = 1.0f);
					static void DrawQuad(const Vec3& position, const Vec2& size, const glm::float32 rotation, const Ref<Interface::Textures::Texture2D>& texture, const Vec4& color, float tilingFactor = 1.0f);

				public: // Debug & Profiler structs
					struct Statistics
					{
						UInt drawCalls = 0;
						UInt quadCount = 0;

						UInt GetTotalVertexCount() { return quadCount * 4; }
						UInt GetTotalIndexCount() { return quadCount * 6; }
					};

				public:	// Debug & Profile
					static void ResetStatistics();
					static Statistics GetStatistics();
				};
			}
		}
	}
}

#endif // !RENDERER_2D_H
