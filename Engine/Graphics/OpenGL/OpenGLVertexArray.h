#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "../VertexArray.h"
#include "../Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLVertexArray : public VertexArray
				{
				public: // Ctor / Dtor
					OpenGLVertexArray();

					~OpenGLVertexArray();

				public:
					virtual void Bind() const override;

					virtual void Unbind() const override;

				public: // Get / Set
					virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

					virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

					inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; };

					inline virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; };

				private:
					uint32_t rendererID;
					std::vector<Ref<VertexBuffer>> vertexBuffers;
					Ref<IndexBuffer> indexBuffer;
				};
			}
		}
	}
}


#endif // !OPENGL_VERTEX_ARRAY_H
