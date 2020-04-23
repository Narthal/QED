#ifndef BUFFER_LAYOUT_H
#define BUFFER_LAYOUT_H

#include "Core/Type/Numeric.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace Buffers
				{
					enum class ShaderDataType : uint8_t
					{
						// Default
						NONE = 0,

						// Floats
						Float,
						Float2,
						Float3,
						Float4,

						// Matrixes
						Mat3,
						Mat4,

						// Integers
						Int,
						Int2,
						Int3,
						Int4,

						// Boolean
						Bool,
					};

					static UInt ShaderDataTypeSize(ShaderDataType shaderDataType)
					{
						switch (shaderDataType)
						{
							// NONE
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::NONE:
							// TODO: crash here
							break;

							// Floats												sizeof(float) * n
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float:		return 4 * 1;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float2:		return 4 * 2;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float3:		return 4 * 3;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float4:		return 4 * 4;

								// Matrices												sizeof(float) * n * n
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Mat3:		return 4 * 3 * 3;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Mat4:		return 4 * 4 * 4;

								// Integers												sizeof(int) * n
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int:		return 4 * 1;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int2:		return 4 * 2;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int3:		return 4 * 3;
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int4:		return 4 * 4;

								// Boolean												sizeof(bool)
							case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Bool:		return 1;

								// Default
							default:
							// TODO crash here
							break;
						}

						// TODO: crash here
						return 0;
					}

					struct BufferElement
					{
						std::string name;
						ShaderDataType shaderDataType;
						UInt size;
						UInt offset;
						bool normalized;

					public:
						BufferElement() = delete;

					public:
						BufferElement(ShaderDataType shaderDataType, const std::string name, bool normalized = false)
							: name(name), shaderDataType(shaderDataType), size(ShaderDataTypeSize(shaderDataType)), offset(0), normalized(normalized) {}

					public:
						UInt GetComponentCount() const
						{
							switch (shaderDataType)
							{
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::NONE:
								// TODO: crash here
								return 0;

								// Floats												n
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float:		return 1;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float2:		return 2;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float3:		return 3;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Float4:		return 4;

								// Matrices												n * n
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Mat3:		return 3 * 3;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Mat4:		return 4 * 4;

								// Integers												n
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int:		return 1;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int2:		return 2;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int3:		return 3;
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Int4:		return 4;

								// Boolean												n
								case QED::Engine::Graphics::Interface::Buffers::ShaderDataType::Bool:		return 1;

								// Default
								default:
								// TODO: abort here
								return 0;
							}
						}
					};

					class BufferLayout
					{
					public:
						// Ctor : takes in a list of { shadertype, name, etc }, { ... }
						BufferLayout(const std::initializer_list<BufferElement>& elements)
							: bufferElements(elements)
						{
							CalculateOffsetAndStride();
						}

						BufferLayout() = default;

					public: // Iterators for elements
						inline std::vector<BufferElement>::iterator begin() { return bufferElements.begin(); }
						inline std::vector<BufferElement>::iterator end() { return bufferElements.end(); }
						inline std::vector<BufferElement>::const_iterator begin() const { return bufferElements.begin(); }
						inline std::vector<BufferElement>::const_iterator end() const { return bufferElements.end(); }

					public: // Get / Set
						// bufferElements : buffer layout container
						inline const std::vector<BufferElement>& GetElements() const { return bufferElements; }
						inline UInt GetStride() const { return stride; }

					private: // Internal
						void CalculateOffsetAndStride()
						{
							UInt offset = 0;
							stride = 0;
							for (auto& element : bufferElements)
							{
								element.offset = offset;
								offset += element.size;
								stride += element.size;
							}
						}

					private:
						std::vector<BufferElement> bufferElements;
						UInt stride = 0;
					};
				}
			}
		}
	}
}



#endif // !BUFFER_LAYOUT_H
