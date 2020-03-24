#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

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

					virtual ~OpenGLTexture2D();

				public:
					inline virtual uint32_t GetWidth() const override { return width; }
					inline virtual uint32_t GetHeight() const override { return height; }

					virtual void Bind(uint32_t slot = 0) const override;

				private:
					// TODO: path should be stored in asset manager
					std::string path;
					
					uint32_t width;
					uint32_t height;

					uint32_t RendererID;
				};
			}
		}
	}
}



#endif // !OPENGL_TEXTURE_H
