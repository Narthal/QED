#ifndef TYPE_H
#define TYPE_H


namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Type
			{
				// Scope
				template<typename T>
				using Scope = std::unique_ptr<T>;

				template<typename T, typename ... Args>
				constexpr Scope<T> CreateScope(Args&& ... args)
				{
					return std::make_unique<T>(std::forward<Args>(args)...);
				}

				// Reference
				template<typename T>
				using Ref = std::shared_ptr<T>;
			
				template<typename T, typename ... Args>
				constexpr Ref<T> CreateRef(Args&& ... args)
				{
					return std::make_shared<T>(std::forward<Args>(args)...);
				}
			}
		}
	}

#pragma region NamespaceShortened
	// Shorthand scope
	template<typename T>
	using Scope = Engine::Core::Type::Scope<T>;

	// Shorthand reference
	template<typename T>
	using Ref = Engine::Core::Type::Ref<T>;
#pragma endregion

}


#endif // !TYPE_H
