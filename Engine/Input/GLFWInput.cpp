#include "EnginePCH.h"
#include "GLFWInput.h"


// NOTE: define windows before GLFW to avoid macro redefinition warnings
// TODO: move windows.h to PCH
#include <windows.h>

// GLFW
#include "GLFW/glfw3.h"



#include "../Core/Application/Application.h"



namespace QED
{
	namespace Engine
	{
		namespace Input
		{
			bool GLFWInput::IsKeyPressedImplementation(int keycode)
			{
				// Get window handle & cast it to glfw
				GLFWwindow* windowHandle = (GLFWwindow*)Core::Application::Application::GetInstance().GetWindow()->GetWindowHandle();

				// Get key state
				int state = glfwGetKey(windowHandle, keycode);

				// Return state
				return state == GLFW_PRESS || state == GLFW_REPEAT;
			}
			bool GLFWInput::IsMouseButtonPressedImplementation(int button)
			{
				// Get window handle & cast it to glfw
				GLFWwindow* windowHandle = (GLFWwindow*)Core::Application::Application::GetInstance().GetWindow()->GetWindowHandle();

				// Get mouse button state
				int state = glfwGetMouseButton(windowHandle, button);

				// Return state
				return state == GLFW_PRESS;
			}
			std::pair<float, float> GLFWInput::GetMousePositionImplementation()
			{
				// Get window handle & cast it to glfw
				GLFWwindow* windowHandle = (GLFWwindow*)Core::Application::Application::GetInstance().GetWindow()->GetWindowHandle();

				// Get mouse position
				double x, y;
				glfwGetCursorPos(windowHandle, &x, &y);

				// Return position
				return { (float)x, (float)y };
			}
			float GLFWInput::GetMouseXImplementation()
			{
				auto [x, y] = GetMousePositionImplementation();
				return x;
			}
			float GLFWInput::GetMouseYImplementation()
			{
				auto [x, y] = GetMousePositionImplementation();
				return y;
			}
		}
	}
}



