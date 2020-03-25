#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

// OpenGL
#include <glad/glad.h>

// Inheritance
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
					OpenGLShader(const std::string& path);
					OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
					virtual ~OpenGLShader();

				public:
					virtual void Bind() const override;
					virtual void Unbind() const override;

					virtual void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) override;
					virtual void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& vector) override;
					virtual void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& vector) override;
					virtual void UploadUniformInt(const std::string& uniformName, const uint32_t value) override;

				private:
					std::string ReadFile(const std::string& path);
					std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
					void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

				private:
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_SHADER_H
