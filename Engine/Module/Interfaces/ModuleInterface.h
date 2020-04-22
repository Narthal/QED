#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

#include "../QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			namespace Interfaces
			{
				class QED_ENGINE_API ModuleInterface
				{
				public: // Init / Dtor
					// Initialize
					virtual void Initialize() = 0;
					// Releases resources of a module
					virtual ~ModuleInterface() = 0;

				public: // Utility
					// Gets the name of the module
					virtual const char* GetName() const = 0;
				};
			}
		}
	}
}


#endif // !MODULE_INTERFACE_H
