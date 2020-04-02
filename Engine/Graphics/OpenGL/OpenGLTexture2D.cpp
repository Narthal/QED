#include "enginePCH.h"
#include "OpenGLTexture2D.h"

// Load image from file
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Upload image to GPU
#include <glad/glad.h>

#include "Core/Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path)
				{
					stbi_uc* data;
					int channels;
					// Scoped so local width, heigh can not be used (only the member width, height)
					{
						// Default image load of stb is top to bottom,
						// OpenGL loads textures bottom to top, so it need to be inverted somewhere.
						// stb will flip images after load if this is set to true;
						stbi_set_flip_vertically_on_load(true);

						int width, height;
						data = stbi_load(path.c_str(), &width, &height, &channels, 0);

						QED_CORE_ASSERT(data != nullptr, "Stb couldn't load image at path : {0}", path);
						// Store width, height in member variables & dispose local width, height after scope
						this->width = width;
						this->height = height;
					}

					// Set format data
					GLenum internalFormat = 0;
					GLenum dataFormat = 0;
					if (channels == 4)
					{
						internalFormat = GL_RGBA8;
						dataFormat = GL_RGBA;
					}
					else if (channels == 3)
					{
						internalFormat = GL_RGB8;
						dataFormat = GL_RGB;
					}
					else
					{
						// TODO: throw here!
					}

					// Create OpenGL texture
					glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
					glTextureStorage2D(RendererID, 1, internalFormat, width, height);

					glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

					// TODO: use GL_RGB / GL_RGBA based on channels == 3 or channels == 4
					glTextureSubImage2D(RendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

					// Release data after OpenGL upload
					stbi_image_free(data);

				}

				OpenGLTexture2D::~OpenGLTexture2D()
				{
					glDeleteTextures(1, &RendererID);
				}

				void OpenGLTexture2D::Bind(uint32_t slot) const
				{
					glBindTextureUnit(slot, RendererID);
				}
			}
		}
	}
}



