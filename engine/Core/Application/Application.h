#ifndef APPLICATION_H
#define APPLICATION_H

#include "../QEDApi.h"

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
					Application() {};
					virtual ~Application() {};

					void RunMainLoop();
				private:
					bool isRunning = true;
				};

				// Application implements this function
				Application* CreateApplication();
			}
		}
	}
}

#endif // !APPLICATION_H
