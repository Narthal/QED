#include "EnginePCH.h"
#include "OpenGLContext.h"

// GLFW
#include "GLFW/glfw3.h"

// GLAD
#include "glad/glad.h"

#include "../Core/Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
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

					// Log OpenGL vendor
					LOG << "OpenGL vendor : " << glGetString(GL_VENDOR);

					// Log OpenGL renderer
					LOG  << "OpenGL renderer : " << glGetString(GL_RENDERER);

					// Log OpenGL version
					LOG  << "OpenGL version : " << glGetString(GL_VERSION);


				}

				void OpenGLContext::SwapBuffers()
				{
					glfwSwapBuffers(windowHandle);
				}
			}
		}
	}
}

