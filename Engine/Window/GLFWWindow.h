#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H



// Inheritance
#include "CoreWindow.h"

// GLFW
#include "GLFW/glfw3.h"



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

				virtual void Update() override;


			private:

			};
		}
	}
}

#endif // !GLFW_WINDOW_H
