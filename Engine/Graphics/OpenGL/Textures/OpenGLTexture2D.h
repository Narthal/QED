#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

// GLAD
#include <glad/glad.h>

#include "Core/Type/Numeric.h"

#include "Graphics/Interface/Textures/Texture2D.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace Textures
				{
					class OpenGLTexture2D : public Interface::Textures::Texture2D
					{
					public: // Ctor / Dtor
						OpenGLTexture2D(const std::string& path);
						OpenGLTexture2D(UInt width, UInt height);
						virtual ~OpenGLTexture2D();

					public: // Get / Set
						inline virtual UInt GetWidth() const override { return width; }
						inline virtual UInt GetHeight() const override { return height; }

						virtual void SetData(void* data, UInt size) override;

					public: // Graphics
						virtual void Bind(UInt slot = 0) const override;

					public: // Operators
						inline virtual bool operator==(const Texture& other) const override { return RendererID == ((OpenGLTexture2D&)other).RendererID; };

					private:
						// TODO: path should be stored in asset manager
						std::string path;

						UInt width;
						UInt height;
						GLenum internalFormat = 0;
						GLenum dataFormat = 0;

						UInt RendererID;
					};
				}
			}
		}
	}
}



#endif // !OPENGL_TEXTURE_H
