#ifndef BUFFER_LAYOUT_H
#define BUFFER_LAYOUT_H


namespace QED
{
	namespace Engine
	{
		namespace Graphics
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

			static uint32_t ShaderDataTypeSize(ShaderDataType shaderDataType)
			{
				switch (shaderDataType)
				{
					// NONE
					case QED::Engine::Graphics::ShaderDataType::NONE:
					// TODO: crash here
					break;

					// Floats												sizeof(float) * n
					case QED::Engine::Graphics::ShaderDataType::Float:		return 4 * 1;	
					case QED::Engine::Graphics::ShaderDataType::Float2:		return 4 * 2;
					case QED::Engine::Graphics::ShaderDataType::Float3:		return 4 * 3;
					case QED::Engine::Graphics::ShaderDataType::Float4:		return 4 * 4;

					// Matrices												sizeof(float) * n * n
					case QED::Engine::Graphics::ShaderDataType::Mat3:		return 4 * 3 * 3;
					case QED::Engine::Graphics::ShaderDataType::Mat4:		return 4 * 4 * 4;

					// Integers												sizeof(int) * n
					case QED::Engine::Graphics::ShaderDataType::Int:		return 4 * 1;
					case QED::Engine::Graphics::ShaderDataType::Int2:		return 4 * 2;
					case QED::Engine::Graphics::ShaderDataType::Int3:		return 4 * 3;
					case QED::Engine::Graphics::ShaderDataType::Int4:		return 4 * 4;
					
					// Boolean												sizeof(bool)
					case QED::Engine::Graphics::ShaderDataType::Bool:		return 1;

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
				uint32_t size;
				uint32_t offset;
				bool normalized;
				
				private:
				BufferElement() {}

				public:
				BufferElement(ShaderDataType shaderDataType, const std::string name, bool normalized = false)
					: name(name), shaderDataType(shaderDataType), size(ShaderDataTypeSize(shaderDataType)), offset(0), normalized(normalized) {}

				public:
				uint32_t GetComponentCount() const
				{
					switch (shaderDataType)
					{
						case QED::Engine::Graphics::ShaderDataType::NONE:
						// TODO: crash here
						break;

						// Floats												n
						case QED::Engine::Graphics::ShaderDataType::Float:		return 1;
						case QED::Engine::Graphics::ShaderDataType::Float2:		return 2;
						case QED::Engine::Graphics::ShaderDataType::Float3:		return 3;
						case QED::Engine::Graphics::ShaderDataType::Float4:		return 4;
						
						// Matrices												n * n
						case QED::Engine::Graphics::ShaderDataType::Mat3:		return 3 * 3;
						case QED::Engine::Graphics::ShaderDataType::Mat4:		return 4 * 4;

						// Integers												n
						case QED::Engine::Graphics::ShaderDataType::Int:		return 1;
						case QED::Engine::Graphics::ShaderDataType::Int2:		return 2;
						case QED::Engine::Graphics::ShaderDataType::Int3:		return 3;
						case QED::Engine::Graphics::ShaderDataType::Int4:		return 4;

						// Boolean												n
						case QED::Engine::Graphics::ShaderDataType::Bool:		return 1;
						break;

						// Default
						default:
						break;
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

				public:
				BufferLayout() {};

				
				// Iterators for elements
				public:
				inline std::vector<BufferElement>::iterator begin() { return bufferElements.begin(); }

				public:
				inline std::vector<BufferElement>::iterator end() { return bufferElements.end(); }

				public:
				inline std::vector<BufferElement>::const_iterator begin() const { return bufferElements.begin(); }

				public:
				inline std::vector<BufferElement>::const_iterator end() const { return bufferElements.end(); }


				// bufferElements : buffer layout container
				public:
				// Get
				inline const std::vector<BufferElement>& GetElements() const { return bufferElements; }
				private:
				// Container
				std::vector<BufferElement> bufferElements;

				public:
				inline uint32_t GetStride() const { return stride; }

				private:
				uint32_t stride = 0;


				private:
				void CalculateOffsetAndStride()
				{
					uint32_t offset = 0;
					stride = 0;
					for (auto& element : bufferElements)
					{
						element.offset = offset;
						offset += element.size;
						stride += element.size;
					}
				}
			};
		}
	}
}



#endif // !BUFFER_LAYOUT_H
