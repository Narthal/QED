#ifndef SHADER_H
#define SHADER_H

// GLM
#include <glm/glm.hpp>

#include "../Module/QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API Shader
			{
			public:
				static Shader* Create(const std::string& path);
				static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
				virtual ~Shader() {}

			public:
				virtual void Bind() const = 0;
				virtual void Unbind() const = 0;

				virtual void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) = 0;
				virtual void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& vector) = 0;
				virtual void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& vector) = 0;
				virtual void UploadUniformInt(const std::string& uniformName, const uint32_t value) = 0;
			};
		}
	}
}



#endif // !SHADER_H
