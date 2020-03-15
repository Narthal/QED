#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "BufferLayout.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class VertexBuffer
			{
				public:
				virtual ~VertexBuffer() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				static VertexBuffer* Create(float* vertices, unsigned int size);

				public:
				virtual void SetLayout(const BufferLayout& layout) = 0;

				public:
				virtual const BufferLayout& GetLayout() const = 0;
			};
		}
	}
}

#endif // !VERTEX_BUFFER_H
