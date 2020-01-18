#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H



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
					: width(width), height(height), isVsync(isVsync), isFullscreen(isFullscreen) {}

				virtual ~CoreWindow() = 0;



			private:
				int width;
				int height;
				bool isVsync;
				bool isFullscreen;

			protected:
				void* windowHandle;
				ContextType contextType;
			};

			CoreWindow::~CoreWindow() {}
		}
	}
}



#endif // !CORE_WINDOW_H
