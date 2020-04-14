#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <glad\glad.h>

#include "../Texture2D.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLTexture2D : public Texture2D
				{
				public:
					OpenGLTexture2D(const std::string& path);
					OpenGLTexture2D(uint32_t width, uint32_t height);

					virtual ~OpenGLTexture2D();

				public:
					inline virtual uint32_t GetWidth() const override { return width; }
					inline virtual uint32_t GetHeight() const override { return height; }

					virtual void SetData(void* data, uint32_t size) override;

					virtual void Bind(uint32_t slot = 0) const override;

				private:
					// TODO: path should be stored in asset manager
					std::string path;
					
					uint32_t width;
					uint32_t height;
					GLenum internalFormat = 0;
					GLenum dataFormat = 0;


					uint32_t RendererID;
				};
			}
		}
	}
}



#endif // !OPENGL_TEXTURE_H
