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
				Shader(const std::string& vertexSource, const std::string& fragmentSource);
				
				public:
				~Shader();

				public:
				void Bind() const;
				
				public:
				void Unbind() const;
			
				private:
				unsigned int rendererID;
			};
		}
	}
}



#endif // !SHADER_H
