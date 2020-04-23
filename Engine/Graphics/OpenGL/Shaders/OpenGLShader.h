#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

// GLAD
#include <glad/glad.h>

#include "Graphics/Interface/Shaders/Shader.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				namespace Shaders
				{
					class OpenGLShader : public Interface::Shaders::Shader
					{
					public: // Ctor / Dtor
						OpenGLShader(const std::string& path);
						OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
						virtual ~OpenGLShader();

					public: // Utility
						inline virtual const std::string& GetName() const override { return name; }

					public: // Graphics
						virtual void Bind() const override;
						virtual void Unbind() const override;

					public: // Uniform setters
						virtual void SetMat4(const std::string& uniformName, const Mat4& matrix) override;
						virtual void SetFloat4(const std::string& uniformName, const Vec4& vector) override;
						virtual void SetFloat3(const std::string& uniformName, const Vec3& vector) override;
						virtual void SetFloat(const std::string& uniformName, float value) override;
						virtual void SetInt(const std::string& uniformName, UInt value) override;
						virtual void SetIntArray(const std::string& uniformName, UInt* values, UInt count) override;

					private:
						std::string ReadFile(const std::string& path);
						std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
						void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

					private:
						unsigned int rendererID;
						std::string name;
					};
				}
			}
		}
	}
}

#endif // !OPENGL_SHADER_H
