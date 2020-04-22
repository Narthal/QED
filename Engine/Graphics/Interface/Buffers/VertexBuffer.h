#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

#include "BufferLayout.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API VertexBuffer
			{
			public: // Ctor / Dtor
				static Ref<VertexBuffer> Create(uint32_t size);
				static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
				virtual ~VertexBuffer() {}

			public:
				virtual void Bind() const = 0;
				virtual void Unbind() const = 0;

			public: // Get / Set
				virtual void SetLayout(const BufferLayout& layout) = 0;
				virtual const BufferLayout& GetLayout() const = 0;

				virtual void SetData(const void* data, uint32_t size) = 0;
			};
		}
	}
}

#endif // !VERTEX_BUFFER_H
