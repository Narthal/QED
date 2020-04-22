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

				template<typename T>
				constexpr bool ObjectEquals(Scope<T> a, Scope<T> b)
				{
					return *a.get() == *b.get();
				}

				// Reference
				template<typename T>
				using Ref = std::shared_ptr<T>;
			
				template<typename T, typename ... Args>
				constexpr Ref<T> CreateRef(Args&& ... args)
				{
					return std::make_shared<T>(std::forward<Args>(args)...);
				}

				template<typename T>
				constexpr bool ObjectEquals(Ref<T> a, Ref<T> b)
				{
					return *a.get() == *b.get();
				}
			}
		}
	}

	using namespace QED::Engine::Core::Type;
}


#endif // !TYPE_H
