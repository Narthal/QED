#ifndef RENDERER_API_H
#define RENDERER_API_H

// GLM
#include <glm/glm.hpp>

#include "VertexArray.h"

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
				virtual void Clear() = 0;

				public:
				virtual void SetClearColor(const glm::vec4 color) = 0;

				public:
				virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) = 0;

				public:
				inline static API GetAPI() { return api; }

				private:
				static API api;
			};
		}
	}
}

#endif // !RENDERER_API_H
