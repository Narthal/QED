#include "enginePCH.h"
#include "ShaderLibrary.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
			{
				// TODO: crash if Exists(name) == true, "shader already exists with name " << name;
				shaders[name] = shader;
			}

			void ShaderLibrary::Add(const Ref<Shader>& shader)
			{
				const std::string& name = shader->GetName();
				Add(name, shader);
			}

			Ref<Shader> ShaderLibrary::Load(const std::string& path)
			{
				Ref<Shader> shader = Shader::Create(path);
				Add(shader);
				return shader;
			}

			Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
			{
				Ref<Shader> shader = Shader::Create(path);
				Add(name, shader);
				return shader;
			}

			Ref<Shader> ShaderLibrary::Get(const std::string& name)
			{
				// TODO: crash if Exists(name) == false, "shader not found with name " << name;
				return shaders[name];
			}
			bool ShaderLibrary::Exists(const std::string& name)
			{
				return shaders.find(name) != shaders.end();
			}
		}
	}
}



