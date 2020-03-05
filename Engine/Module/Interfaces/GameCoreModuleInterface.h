#ifndef GAME_CORE_MODULE_INTERFACE_H
#define GAME_CORE_MODULE_INTERFACE_H

#include "ModuleInterface.h"

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			namespace Interfaces
			{
				class GameCoreModuleInterface : public ModuleInterface
				{
					public:
					virtual void GameCoreTest() = 0;

				};
			}
		}
	}
}


#endif // !GAME_CORE_MODULE_INTERFACE_H
