#ifndef KERNEL_H
#define KERNEL_H

#include "QEDApi.h"
#include"Interfaces/ModuleInterface.h"
#include "LoadModule.h"

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			class Kernel
			{
				std::list<Interfaces::ModuleInterface*> modules;
			
				public:
				Kernel()
				{
					modules.emplace_back(Module::Load("C:\\Users\\balas\\source\\GitHubRepos\\QED\\Build\\Sandbox\\Debug-windows-x86_64\\Sandbox.dll"))
				}
			};
		}
	}
}


#endif // !KERNEL_H
