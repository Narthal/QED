#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			namespace Interfaces
			{
				class ModuleInterface
				{
					public:
					// Releases resources of a module
					virtual ~ModuleInterface() = 0;

					public:
					// Gets the name of the module
					virtual const char* GetName() const = 0;

				};
			}
		}
	}
}


#endif // !MODULE_INTERFACE_H
