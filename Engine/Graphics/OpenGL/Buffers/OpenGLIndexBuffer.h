#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include "Graphics/Interface/Buffers/IndexBuffer.h"
#include "Core/Type/Numeric.h"

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
						OpenGLIndexBuffer(UInt* indices, UInt count);
						virtual ~OpenGLIndexBuffer();

					public:
						virtual void Bind() const;
						virtual void Unbind() const;

					public:
						inline virtual UInt GetCount() const override { return count; }

					private:
						UInt rendererID;
						UInt count;
					};
				}
			}
		}
	}
}


#endif // !OPENGL_INDEX_BUFFER_H
