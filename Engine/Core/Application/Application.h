#ifndef APPLICATION_H
#define APPLICATION_H

#include "../QEDApi.h"
#include "../Window/CoreWindow.h"
#include "../Event/WindowEvent.h"

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

					void OnEvent(Event::Event& event);

					void RunMainLoop();
				private:
					bool isRunning = true;
					Window::CoreWindow* window;

					bool OnWindowClose(Event::WindowCloseEvent& event);
				};

				// Application implements this function
				Application* CreateApplication();
			}
		}
	}
}

#endif // !APPLICATION_H
