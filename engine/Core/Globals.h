#ifndef GLOBALS_H
#define GLOBALS_H


#include "QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Registry
			{
				template <class K, class V, class Compare = std::less<K>, class Allocator = std::allocator<std::pair<const K, V>>>
				class GuardedMap;
			}


			namespace Globals
			{
				Registry::GuardedMap<std::string, std::string>* registry;
			}
		}
	}
}


#endif // !GLOBALS_H
