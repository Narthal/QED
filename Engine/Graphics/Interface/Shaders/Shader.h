#ifndef SHADER_H
#define SHADER_H


#include "Core/Type/Reference.h"
#include "Core/Type/Numeric.h"

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
					class Shader
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
						virtual void SetMat4(const std::string& uniformName, const Mat4& matrix) = 0;
						virtual void SetFloat4(const std::string& uniformName, const Vec4& vector) = 0;
						virtual void SetFloat3(const std::string& uniformName, const Vec3& vector) = 0;
						virtual void SetFloat(const std::string& uniformName, float value) = 0;
						virtual void SetInt(const std::string& uniformName, UInt value) = 0;
						virtual void SetIntArray(const std::string& uniformName, UInt* values, UInt count) = 0;
					};
				}
			}
		}
	}
}



#endif // !SHADER_H
