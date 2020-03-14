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

					public:
					virtual ~OpenGLShader();

					public:
					virtual void Bind() const;

					public:
					virtual void Unbind() const;

					private:
					unsigned int rendererID;
				};
			}
		}
	}
}

#endif // !OPENGL_SHADER_H
