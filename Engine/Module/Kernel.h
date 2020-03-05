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
	
				public:
				Kernel()
				{
					Module* mod = new Module("C:\\Users\\balas\\source\\GitHubRepos\\QED\\Build\\Sandbox\\Debug-windows-x86_64\\Sandbox");
					mod->interfaces[0]->Initialize();
					std::string name = mod->interfaces[0]->GetName();
					std::cout << "Module name : " << mod->moduleName << std::endl;
					std::cout << "Module interface name : " << name << std::endl;
				}
			};
		}
	}
}


#endif // !KERNEL_H
