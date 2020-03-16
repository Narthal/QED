#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class VertexArray
			{
				public:
				~VertexArray() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

				public:
				virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

				public:
				virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;

				public:
				virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

				public:
				static VertexArray* Create();
			};
		}
	}
}


#endif // !VERTEX_ARRAY_H
