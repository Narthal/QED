#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

// Module
#include "../Module/QEDApi.h"

// Inheritance
#include "Texture.h"

#include "../Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API Texture2D : public Texture
			{
			public:
				static Ref<Texture2D> Create(const std::string& path);
				static Ref<Texture2D> Create(uint32_t width, uint32_t height);
			};
		}
	}
}



#endif // !TEXTURE_2D_H
