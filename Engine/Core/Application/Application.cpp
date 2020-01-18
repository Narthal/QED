#include "EnginePCH.h"
#include "Application.h"

// TODO: remove this
#include "../Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::RunMainLoop()
			{
				while (isRunning)
				{
					std::cout << "a" << std::endl;
				};
			}
		}
	}
}


