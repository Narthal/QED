#include "EnginePCH.h"
#include "OpenGLContext.h"

// GLFW
#include "GLFW/glfw3.h"

// GLAD
#include "glad/glad.h"

namespace QED
{
	namespace Engine
	{
		namespace Renderer
		{
			namespace OpenGL
			{
				OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : windowHandle(windowHandle)
				{
					// TODO: assert ceck window handle is valid
				}

				void OpenGLContext::Init()
				{
					// Set context to current
					glfwMakeContextCurrent((GLFWwindow*)windowHandle);

					// GLAD
					int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
					// TODO: assert status
				}

				void OpenGLContext::SwapBuffers()
				{
					glfwSwapBuffers(windowHandle);
				}
			}
		}
	}
}

