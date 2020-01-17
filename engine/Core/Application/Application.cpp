#include "EnginePCH.h"
#include "Application.h"

// TODO: remove this
#include "../Event/WindowEvent.h"
#include "../Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			void Application::Application::RunMainLoop()
			{
				Event::WindowResizeEvent e(1280, 720);
				Log::LogLine() << e;

				while (true)
				{
					//std::cout << "a" << std::endl;
				};
			}
		}
	}
}


