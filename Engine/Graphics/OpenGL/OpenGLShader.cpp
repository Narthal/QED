#include "EnginePCH.h"
#include "OpenGLShader.h"



// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Log
#include "../../Core/Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				static GLenum ShaderTypeFromString(const std::string& type)
				{
					if (type == "vertex")
					{
						return GL_VERTEX_SHADER;
					}
					else if (type == "fragment")
					{
						return GL_FRAGMENT_SHADER;
					}
					else
					{
						// TODO: crash here!
						return 0;
					}
				}

				OpenGLShader::OpenGLShader(const std::string& path)
				{
					std::string source = ReadFile(path);
					auto shaderSources = PreProcess(source);
					Compile(shaderSources);
				}

				OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
				{
					std::unordered_map<GLenum, std::string> shaderSources;
					shaderSources[GL_VERTEX_SHADER] = vertexSource;
					shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
					Compile(shaderSources);
				}

				OpenGLShader::~OpenGLShader()
				{
					glDeleteProgram(rendererID);
				}

				void OpenGLShader::Bind() const
				{
					glUseProgram(rendererID);
				}

				void OpenGLShader::Unbind() const
				{
					glUseProgram(0);
				}

				void OpenGLShader::UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix)
				{
					GLint location = glGetUniformLocation(rendererID, uniformName.c_str());
					// TODO: assert if location == -1
					glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
				}

				void OpenGLShader::UploadUniformFloat4(const std::string& uniformName, const glm::vec4& vector)
				{
					GLint location = glGetUniformLocation(rendererID, uniformName.c_str());
					// TODO: assert if location == -1
					glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
				}

				void OpenGLShader::UploadUniformFloat3(const std::string& uniformName, const glm::vec3& vector)
				{
					GLint location = glGetUniformLocation(rendererID, uniformName.c_str());
					// TODO: assert if location == -1
					glUniform3f(location, vector.x, vector.y, vector.z);
				}

				void OpenGLShader::UploadUniformInt(const std::string& uniformName, const uint32_t value)
				{
					GLint location = glGetUniformLocation(rendererID, uniformName.c_str());
					// TODO: assert if location == -1
					glUniform1i(location, value);
				}

				std::string OpenGLShader::ReadFile(const std::string& path)
				{
					std::string result;
					std::ifstream in(path, std::ios::in, std::ios::binary);

					// Error handling
					if (!in)
					{
						// TODO: crash here!
						return "";
					}

					// Get size & resize result
					in.seekg(0, std::ios::end);
					result.resize(in.tellg());
					in.seekg(0, std::ios::beg);

					// Read to result
					in.read(&result[0], result.size());

					// Close file
					in.close();

					return result;
				}

				std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
				{
					std::unordered_map<GLenum, std::string> shaderSources;

					const char* typeToken = "#type";
					size_t typeTokenLength = strlen(typeToken);
					size_t pos = source.find(typeToken, 0);

					while (pos != std::string::npos)
					{
						size_t eol = source.find_first_of("\r\n", pos);
						// TODO: assert eol != std::string::npos, "Syntax error"
						size_t begin = pos + typeTokenLength + 1;
						std::string type = source.substr(begin, eol - begin);
						// TODO: assert type == "vertex" | type == "fragment", "Invalid shader type specifier"

						size_t nextLinePos = source.find_first_of("\r\n", eol);
						pos = source.find(typeToken, nextLinePos);
						shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
					}

					return shaderSources;
				}

				void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
				{
					GLuint programID = glCreateProgram();

					std::vector<GLenum> shaderIDs;

					for (auto& shaderData : shaderSources)
					{
						GLenum shaderType = shaderData.first;
						const std::string& shaderSource = shaderData.second;

						GLuint shader = glCreateShader(shaderType);

						const GLchar* sourceCStr = shaderSource.c_str();
						glShaderSource(shader, 1, &sourceCStr, 0);

						glCompileShader(shader);

						GLint isCompiled = 0;
						glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
						if (isCompiled == GL_FALSE)
						{
							GLint maxLength = 0;
							glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

							// Get info on why compillation failed
							std::vector<GLchar> infoLog(maxLength);
							glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

							// Dispose
							glDeleteShader(shader);

							// TODO: crash here!
							LOG << "Shader compillation failure : " << Core::Log::Severity::Error << infoLog.data();

							return;
						}

						glAttachShader(programID, shader);
						shaderIDs.push_back(shader);
					}

					glLinkProgram(programID);

					GLint isLinked = 0;
					glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
					if (isLinked == GL_FALSE)
					{
						GLint maxLength = 0;
						glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

						// Get info on why linking failed
						std::vector<GLchar> infoLog(maxLength);
						glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

						// Dispose
						glDeleteProgram(programID);
						for (auto shader : shaderIDs)
						{
							glDeleteShader(shader);
						}

						// Use the infoLog as you see fit.
						LOG << "Shader program linking failure : " << Core::Log::Severity::Error << infoLog.data();

						// TODO: crash here!
						return;
					}

					// Detach shaders after a link
					for (auto shader : shaderIDs)
					{
						glDetachShader(programID, shader);
					}

					// Only set rendererID if all compillation succeeded
					rendererID = programID;

					return;
				}
			}
		}
	}
}
