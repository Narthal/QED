#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class Shader
			{
			public:
				static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
				virtual ~Shader() {}

			public:
				virtual void Bind() const = 0;
				virtual void Unbind() const = 0;

				virtual void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) = 0;
			};
		}
	}
}



#endif // !SHADER_H
