#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include "Graphics/Interface/Buffers/IndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace Buffers
				{
					class OpenGLIndexBuffer : public Interface::Buffers::IndexBuffer
					{
					public:
						OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
						virtual ~OpenGLIndexBuffer();

					public:
						virtual void Bind() const;
						virtual void Unbind() const;

					public:
						inline virtual uint32_t GetCount() const override { return count; }

					private:
						uint32_t rendererID;
						uint32_t count;
					};
				}
			}
		}
	}
}


#endif // !OPENGL_INDEX_BUFFER_H
