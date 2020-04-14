#ifndef TEXTURE_H
#define TEXTURE_H

#include "Module/QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API Texture
			{
			public:
				virtual ~Texture() = default;

			public:
				virtual uint32_t GetWidth() const = 0;
				virtual uint32_t GetHeight() const = 0;

				virtual void SetData(void* data, uint32_t size) = 0;

				virtual void Bind(uint32_t slot = 0) const = 0;
			};
		}
	}
}



#endif // !TEXTURE_H
