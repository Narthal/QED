#ifndef RENDERER_API_H
#define RENDERER_API_H

// GLM
#include <glm/glm.hpp>

#include "Core/Type/Type.h"

#include "Graphics/Interface/Buffers/VertexArray.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class RendererAPI
			{
			public:
				enum class API
				{
					NONE = 0,
					OpenGL = 1,
				};

			public:
				virtual void Initialize() = 0;

			public:
				virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
				virtual void Clear() = 0;
				virtual void SetClearColor(const glm::vec4 color) = 0;
				virtual void Draw(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

			public:
				inline static API GetAPI() { return api; }

			private:
				static API api;
			};
		}
	}
}

#endif // !RENDERER_API_H
