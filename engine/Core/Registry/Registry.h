#ifndef REGISTRY_H
#define REGISTRY_H

#include <map>
#include <mutex>
#include <string>
#include <tuple>

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Registry
			{
				template <class K, class V, class Compare = std::less<K>, class Allocator = std::allocator<std::pair<const K, V>>>
				class GuardedMap
				{
				private:
					// Variables
					std::map<K, V, Compare, Allocator> map;
					std::mutex m;

					// Singleton
					GuardedMap() {};
				public:
					// Singleton
					GuardedMap(const GuardedMap&) = delete;
					GuardedMap& operator=(const GuardedMap&) = delete;

					// Singleton instance handler
					static GuardedMap& instance()
					{
						static GuardedMap instance;
						return instance;
					}

					#pragma region Map functions


					inline void Set(K key, V value)
					{
						std::lock_guard<std::mutex> lk(this->m);
						this->map[key] = value;
					}

					inline void Set(std::tuple<K, V> tuple)
					{
						std::lock_guard<std::mutex> lk(this->m);
						this->map[tuple[0]] = tuple[1];
					}

					inline V& Get(K key)
					{
						std::lock_guard<std::mutex> lk(this->m);
						return this->map[key];
					}

					inline bool Empty()
					{
						std::lock_guard<std::mutex> lk(this->m);
						return this->map.empty();
					}


					#pragma endregion
				};

				void InitializeRegistry();
			}
		}
	}
}



#endif // !REGISTRY_H
