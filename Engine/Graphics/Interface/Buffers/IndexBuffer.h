#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "Module/QEDApi.h"
#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

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
						static Ref<IndexBuffer> Create(UInt* indices, UInt count);
						virtual ~IndexBuffer() {}

					public:
						virtual void Bind() const = 0;
						virtual void Unbind() const = 0;

					public:
						virtual UInt GetCount() const = 0;
					};
				}
			}
		}
	}
}


#endif // !INDEX_BUFFER_H
