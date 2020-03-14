#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

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
			};
		}
	}
}

#endif // !VERTEX_BUFFER_H
