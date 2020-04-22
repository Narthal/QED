#include "EnginePCH.h"
#include "OpenGLContext.h"

// GLFW
#include <GLFW/glfw3.h>

// GLAD
#include <glad/glad.h>

#include "Core/Log/Log.h"

#include "Profiler/Instrumentor.h"

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
					QED_CORE_ASSERT(windowHandle != nullptr, "OpenGLContext : window handle is null");
				}

				void OpenGLContext::Init()
				{
					QED_PROFILE_FUNCTION();

					// Set context to current
					glfwMakeContextCurrent((GLFWwindow*)windowHandle);

					// GLAD
					int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
					// TODO: assert status
					QED_CORE_ASSERT(status != NULL, "GLAD failed to load");

					// Log OpenGL vendor
					QED_CORE_LOG_INFO("OpenGL vendor : {0}", glGetString(GL_VENDOR));

					// Log OpenGL renderer
					QED_CORE_LOG_INFO("OpenGL renderer : {0}", glGetString(GL_RENDERER));

					// Log OpenGL version
					QED_CORE_LOG_INFO("OpenGL version : {0}", glGetString(GL_VERSION));


				}

				void OpenGLContext::SwapBuffers()
				{
					QED_PROFILE_FUNCTION();

					glfwSwapBuffers(windowHandle);
				}
			}
		}
	}
}

