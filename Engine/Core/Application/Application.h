#ifndef APPLICATION_H
#define APPLICATION_H

#include "../QEDApi.h"
#include "../Window/CoreWindow.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Application
			{
				class QED_API Application
				{
				public:
					Application() { Initialize(); };
					virtual ~Application() {};

					void Initialize();

					void RunMainLoop();
				private:
					bool isRunning = true;
					Window::CoreWindow* window;
				};

				// Application implements this function
				Application* CreateApplication();
			}
		}
	}
}

#endif // !APPLICATION_H
