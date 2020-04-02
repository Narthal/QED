#ifndef KERNEL_H
#define KERNEL_H

#include "QEDApi.h"
#include "Module.h"
#include "Interfaces/ModuleInterface.h"
#include "Core\Log\Log.h"

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
					QED_CORE_LOG_INFO("Module name : {0}", mod->moduleName);
					QED_CORE_LOG_INFO("Module interface name : {0}", name);
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
