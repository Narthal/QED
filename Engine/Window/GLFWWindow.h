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
			public:
				GLFWWindow();

				virtual ~GLFWWindow() override;

				virtual void OnUpdate() override;

				virtual void SetEventCallback(std::function<void(Event::Event&)> callback) override;

				inline virtual void* GetWindowHandle() const { return windowHandle; }

			private:

			};
		}
	}
}

#endif // !GLFW_WINDOW_H
