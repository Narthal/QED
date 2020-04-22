#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "Core/Type/Type.h"

#include "Graphics/Interface/Buffers/VertexArray.h"

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
					class OpenGLVertexArray : public Interface::Buffers::VertexArray
					{
					public: // Ctor / Dtor
						OpenGLVertexArray();

						~OpenGLVertexArray();

					public:
						virtual void Bind() const override;

						virtual void Unbind() const override;

					public: // Get / Set
						virtual void AddVertexBuffer(const Ref<Interface::Buffers::VertexBuffer>& vertexBuffer) override;

						virtual void SetIndexBuffer(const Ref<Interface::Buffers::IndexBuffer>& indexBuffer) override;

						inline virtual const std::vector<Ref<Interface::Buffers::VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; };

						inline virtual const Ref<Interface::Buffers::IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; };

					private:
						uint32_t rendererID;
						std::vector<Ref<Interface::Buffers::VertexBuffer>> vertexBuffers;
						Ref<Interface::Buffers::IndexBuffer> indexBuffer;
					};
				}
			}
		}
	}
}


#endif // !OPENGL_VERTEX_ARRAY_H