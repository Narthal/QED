#ifndef TEXTURE_H
#define TEXTURE_H

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class Texture
			{
			public:
				virtual ~Texture() = default;

			public:
				virtual uint32_t GetWidth() const = 0;
				virtual uint32_t GetHeight() const = 0;

				virtual void Bind(uint32_t slot = 0) const = 0;
			};
		}
	}
}



#endif // !TEXTURE_H
