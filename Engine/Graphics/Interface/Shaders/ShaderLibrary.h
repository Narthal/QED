#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "Core/Type/Type.h"

#include "Shader.h"

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
					class ShaderLibrary
					{
					public: // Load
						Ref<Shader> Load(const std::string& path);
						Ref<Shader> Load(const std::string& name, const std::string& path);
					
					public: // Get / Set
						void Add(const std::string& name, const Ref<Shader>& shader);
						void Add(const Ref<Shader>& shader);

						Ref<Shader> Get(const std::string& name);

					public: // Utility
						bool Exists(const std::string& name);

					private:
						std::unordered_map<std::string, Ref<Shader>> shaders;
					};
				}
			}
		}
	}
}



#endif // !SHADER_LIBRARY_H
