#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class IndexBuffer
			{
				public:
				virtual ~IndexBuffer() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				static IndexBuffer* Create(unsigned int* indices, unsigned int size);

				public:
				virtual unsigned int GetCount() const = 0;
			};
		}
	}
}


#endif // !INDEX_BUFFER_H
