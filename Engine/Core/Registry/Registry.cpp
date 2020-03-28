#include "EnginePCH.h"
#include "Registry.h"


#include "../Globals.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Registry
			{
				void InitializeRegistry()
				{
					Core::Globals::registry->Set("EngineName", "QED");
				}
			}
		}
	}
}


