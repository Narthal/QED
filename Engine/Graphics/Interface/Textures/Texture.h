#ifndef TEXTURE_H
#define TEXTURE_H

#include "Module/QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Textures
				{
					class QED_ENGINE_API Texture
					{
					public: // Ctor / Dtor
						virtual ~Texture() = default;

					public: // Get/ Set
						virtual uint32_t GetWidth() const = 0;
						virtual uint32_t GetHeight() const = 0;

						virtual void SetData(void* data, uint32_t size) = 0;

					public: // Graphics calls
						virtual void Bind(uint32_t slot = 0) const = 0;

					public: // Operators
						virtual bool operator==(const Texture& other) const = 0;
					};
				}
			}
		}
	}
}



#endif // !TEXTURE_H
