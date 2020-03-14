#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include "../IndexBuffer.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLIndexBuffer : public IndexBuffer
				{
					public:
					OpenGLIndexBuffer(unsigned int* indices, unsigned int size);

					public:
					virtual ~OpenGLIndexBuffer();

					public:
					virtual void Bind() const;

					public:
					virtual void Unbind() const;

					public:
					virtual unsigned int GetCount() const { return count; }

					private:
					unsigned int rendererID;

					private:
					unsigned int count;
				};
			}
		}
	}
}


#endif // !OPENGL_INDEX_BUFFER_H
