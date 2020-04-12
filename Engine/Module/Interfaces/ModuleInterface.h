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
					public:
					// Releases resources of a module
					virtual ~ModuleInterface() = 0;

					public:
					// Gets the name of the module
					virtual const char* GetName() const = 0;

					public:
					// Initialize
					virtual void Initialize() = 0;

				};
			}
		}
	}
}


#endif // !MODULE_INTERFACE_H
