#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H



// Inheritance
#include "CoreWindow.h"



namespace QED
{
	namespace Engine
	{
		namespace Window
		{
			class GLFWWindow : public CoreWindow
			{
			public: // Ctor / Dtor
				GLFWWindow();
				virtual ~GLFWWindow() override;

			public: // Window events
				virtual void OnUpdate() override;

			public: // Callback setters
				virtual void SetEventCallback(std::function<void(Event::Event&)> callback) override;

			public: // Get
				inline virtual void* GetWindowHandle() const { return windowHandle; }
			};
		}
	}
}

#endif // !GLFW_WINDOW_H
