#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

// Log
#include "../Core/Log/Log.h"
using namespace QED::Engine::Core::Log;

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
				GLFWWindow()
				{
					glfwInit();
					windowHandle = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
				}

				virtual ~GLFWWindow() override
				{
					glfwDestroyWindow((GLFWwindow*)windowHandle);
					LogLine() << "GLFW window is closing";
				};

			private:

			};
		}
	}
}

#endif // !GLFW_WINDOW_H
