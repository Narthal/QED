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
				QED_ENGINE_API class ModuleInterface
				{
					public:
					// Releases resources of a module
					virtual ~ModuleInterface() {};

					public:
					// Gets the name of the module
					virtual const std::string& GetName() const = 0;

				};
			}
		}
	}
}


#endif // !MODULE_INTERFACE_H
