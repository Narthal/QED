#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "../Event/Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Window
		{
			enum class ContextType
			{
				None,
				OpenGL,
				Other
			};

			class CoreWindow
			{
			public:
				CoreWindow(int width = 1280, int height = 720, bool isVsync = true, bool isFullscreen = false)
				{
					windowData.width = width;
					windowData.height = height;
					windowData.isVsync = isVsync;
					windowData.isFullscreen = isFullscreen;
				}

				virtual ~CoreWindow() {};

				virtual void Update() {};

				virtual void SetEventCallback(std::function<void(Event::Event&)> callback) = 0;

			protected:
				struct WindowData
				{
					// Basic properties
					int width;
					int height;
					bool isVsync;
					bool isFullscreen;

					// Event callback
					std::function<void(Event::Event&)> callback;
				};

				// Basic data
				WindowData windowData;

				// Window implementation
				void* windowHandle;
				ContextType contextType;
				
			};

			//CoreWindow::~CoreWindow() {}
		}
	}
}



#endif // !CORE_WINDOW_H
