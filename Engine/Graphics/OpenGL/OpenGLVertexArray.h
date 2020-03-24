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
					public:
					OpenGLVertexArray();

					public:
					~OpenGLVertexArray();

					public:
					virtual void Bind() const override;

					public:
					virtual void Unbind() const override;

					public:
					virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

					public:
					virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

					public:
					inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; };

					public:
					inline virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; };

					private:
					uint32_t rendererID;

					private:
					std::vector<Ref<VertexBuffer>> vertexBuffers;

					private:
					Ref<IndexBuffer> indexBuffer;
				};
			}
		}
	}
}


#endif // !OPENGL_VERTEX_ARRAY_H
