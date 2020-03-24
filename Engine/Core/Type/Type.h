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
				template<typename T>
				using Scope = std::unique_ptr<T>;

				template<typename T>
				using Ref = std::shared_ptr<T>;
			}
		}
	}

#pragma region NamespaceShortened
	template<typename T>
	using Scope = Engine::Core::Type::Scope<T>;

	template<typename T>
	using Ref = Engine::Core::Type::Ref<T>;
#pragma endregion

}


#endif // !TYPE_H
