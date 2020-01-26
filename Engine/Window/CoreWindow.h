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

				virtual void Update() = 0;

				virtual void SetEventCallback(std::function<void(Event::Event&)> callback) = 0;

				inline int GetWidth() const { return windowData.width; }
				inline int GetHeight() const { return windowData.height; }

				virtual void* GetWindowHandle() const = 0;

			protected:
				// Basic data
				WindowData windowData;

				// Window implementation
				void* windowHandle;
				ContextType contextType;
				
			};
		}
	}
}



#endif // !CORE_WINDOW_H
