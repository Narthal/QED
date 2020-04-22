#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H



#include "Graphics/Interface/API/Context.h"

struct GLFWwindow;

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace OpenGL
			{
				class OpenGLContext : public Context
				{
					public:
					OpenGLContext(GLFWwindow* windowHandle);

					public:
					virtual void Init() override;

					public:
					virtual void SwapBuffers() override;

					private:
					GLFWwindow* windowHandle;
				};
			}
		}
	}
}

#endif // !OPENGL_CONTEXT_H
