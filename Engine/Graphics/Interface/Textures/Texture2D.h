#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "Module/QEDApi.h"
#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

#include "Texture.h"

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
					class QED_ENGINE_API Texture2D : public Texture
					{
					public:
						static Ref<Texture2D> Create(const std::string& path);
						static Ref<Texture2D> Create(UInt width, UInt height);
					};
				}
			}
		}
	}
}



#endif // !TEXTURE_2D_H
