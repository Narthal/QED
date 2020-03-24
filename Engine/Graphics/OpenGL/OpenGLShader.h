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
					virtual void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& vector) override;
					virtual void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& vector) override;

				private:
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_SHADER_H
