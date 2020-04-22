#ifndef SHADER_H
#define SHADER_H

// GLM
#include <glm/glm.hpp>

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Shaders
				{
					class QED_ENGINE_API Shader
					{
					public: // Ctor / Dtor
						static Ref<Shader> Create(const std::string& path);
						static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
						virtual ~Shader() {}

					public: // Utility
						virtual const std::string& GetName() const = 0;

					public: // Graphics
						virtual void Bind() const = 0;
						virtual void Unbind() const = 0;

					public: // Uniform setters
						virtual void SetMat4(const std::string& uniformName, const glm::mat4& matrix) = 0;
						virtual void SetFloat4(const std::string& uniformName, const glm::vec4& vector) = 0;
						virtual void SetFloat3(const std::string& uniformName, const glm::vec3& vector) = 0;
						virtual void SetFloat(const std::string& uniformName, float value) = 0;
						virtual void SetInt(const std::string& uniformName, uint32_t value) = 0;
						virtual void SetIntArray(const std::string& uniformName, uint32_t* values, uint32_t count) = 0;
					};
				}
			}
		}
	}
}



#endif // !SHADER_H
