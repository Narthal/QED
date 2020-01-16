#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>


#include "QEDApi.h"
#include "Registry/Registry.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Globals
			{
				Registry::GuardedMap<std::string, std::string>* registry;
			}
		}
	}
}


#endif // !GLOBALS_H
