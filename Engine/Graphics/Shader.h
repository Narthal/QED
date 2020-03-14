#ifndef SHADER_H
#define SHADER_H



namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class Shader
			{
				public:
				virtual ~Shader() {}

				public:
				virtual void Bind() const = 0;

				public:
				virtual void Unbind() const = 0;

				public:
				static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
			};
		}
	}
}



#endif // !SHADER_H
