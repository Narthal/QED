#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

#include "Graphics/Interface/Buffers/VertexArray.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace API
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
						virtual void SetViewport(UInt x, UInt y, UInt width, UInt height) = 0;
						virtual void Clear() = 0;
						virtual void SetClearColor(const Vec4 color) = 0;
						virtual void Draw(const Ref<Interface::Buffers::VertexArray>& vertexArray, UInt indexCount = 0) = 0;

					public:
						inline static API GetAPI() { return api; }

					private:
						static API api;
					};
				}
			}
		}
	}
}

#endif // !RENDERER_API_H
