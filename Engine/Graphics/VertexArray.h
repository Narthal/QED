#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "../Module/QEDApi.h"
#include "../Core/Type/Type.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API VertexArray
			{
				public:
				~VertexArray() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

				public:
				virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

				public:
				virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

				public:
				virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

				public:
				static Ref<VertexArray> Create();
			};
		}
	}
}


#endif // !VERTEX_ARRAY_H
