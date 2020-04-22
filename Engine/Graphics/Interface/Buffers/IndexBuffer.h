#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

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
					class QED_ENGINE_API IndexBuffer
					{
					public:
						static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
						virtual ~IndexBuffer() {}

					public:
						virtual void Bind() const = 0;
						virtual void Unbind() const = 0;

					public:
						virtual uint32_t GetCount() const = 0;
					};
				}
			}
		}
	}
}


#endif // !INDEX_BUFFER_H
