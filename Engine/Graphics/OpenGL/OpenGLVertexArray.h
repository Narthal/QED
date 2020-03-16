#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "../VertexArray.h"

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
					virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

					public:
					virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

					public:
					inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; };

					public:
					inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; };

					private:
					uint32_t rendererID;

					private:
					std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;

					private:
					std::shared_ptr<IndexBuffer> indexBuffer;
				};
			}
		}
	}
}


#endif // !OPENGL_VERTEX_ARRAY_H
