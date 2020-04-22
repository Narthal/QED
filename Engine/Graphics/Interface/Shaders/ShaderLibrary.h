#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"

#include "Shader.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class QED_ENGINE_API ShaderLibrary
			{
			public:
				void Add(const std::string& name, const Ref<Shader>& shader);
				void Add(const Ref<Shader>& shader);
				Ref<Shader> Load(const std::string& path);
				Ref<Shader> Load(const std::string& name, const std::string& path);

				Ref<Shader> Get(const std::string& name);

				bool Exists(const std::string& name);
			private:
				std::unordered_map<std::string, Ref<Shader>> shaders;
			};
		}
	}
}



#endif // !SHADER_LIBRARY_H
