#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "../Module/QEDApi.h"
#include "Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API IndexBuffer
			{
				public:
				virtual ~IndexBuffer() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int size);

				public:
				virtual unsigned int GetCount() const = 0;
			};
		}
	}
}


#endif // !INDEX_BUFFER_H
