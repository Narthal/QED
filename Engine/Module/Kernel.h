#ifndef KERNEL_H
#define KERNEL_H

#include "QEDApi.h"
#include "Module.h"
#include "Interfaces/ModuleInterface.h"

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			class Kernel
			{
				Module* mod = nullptr;

				public:
				Kernel()
				{
					mod = new Module("C:\\Users\\balas\\source\\GitHubRepos\\QED\\Build\\Sandbox\\Sandbox");
					std::string name = mod->interfaces[0]->GetName();
					std::cout << "Module name : " << mod->moduleName << std::endl;
					std::cout << "Module interface name : " << name << std::endl;
				}

				public:
				~Kernel()
				{
					delete mod;
				}
			};
		}
	}
}


#endif // !KERNEL_H
