#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "../Shader.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLShader : public Shader
				{
				public:
					OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
					virtual ~OpenGLShader();

				public:
					virtual void Bind() const override;
					virtual void Unbind() const override;

					virtual void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) override;

				private:
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_SHADER_H
