#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Buffers
				{
					class QED_ENGINE_API VertexArray
					{
					public: // Ctor / Dtor
						static Ref<VertexArray> Create();

						~VertexArray() = default;

					public:
						virtual void Bind() const = 0;
						virtual void Unbind() const = 0;

					public: // Get / Set
						virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
						virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

						virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
						virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
					};
				}
			}
		}
	}
}


#endif // !VERTEX_ARRAY_H
