#include "EnginePCH.h"
#include "GLFWWindow.h"


// Log
#include "../Core/Log/Log.h"

#include "../Event/Event.h"
#include "../Event/WindowEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace QED
{
	namespace Engine
	{
		namespace Window
		{
			GLFWWindow::GLFWWindow()
			{
				glfwInit();
				windowHandle = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
				glfwMakeContextCurrent((GLFWwindow*)windowHandle);
				glfwSetWindowUserPointer((GLFWwindow*)windowHandle, &windowData);




				// Set GLFW callbacks

				// Set GLFW error callback
				glfwSetErrorCallback([](int error, const char* msg)
				{
						Engine::Core::Log::LogLine() << "GLFW error : " << error << ' ' << msg;
				});

				// Set GLFW resize event
				glfwSetWindowSizeCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, int width, int height)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					data.width = width;
					data.height = height;

					Event::WindowResizeEvent event(width, height);
					data.callback(event);
				});

				// Set GLFW close event
				glfwSetWindowCloseCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					Event::WindowCloseEvent event;
					data.callback(event);
				});

				// Set GLFW keyboard event
				glfwSetKeyCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, int key, int scancode, int action, int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					switch (action)
					{
						case GLFW_PRESS:
						{
							Event::KeyPressedEvent event(key, 0);
							data.callback(event);
							break;
						}
						case GLFW_RELEASE:
						{
							Event::KeyReleasedEvent event(key);
							data.callback(event);
							break;
						}
						case GLFW_REPEAT:
						{
							Event::KeyPressedEvent event(key, 1);
							data.callback(event);
							break;
						}
					}
				});

				// Set GLFW mouse event
				glfwSetMouseButtonCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, int button, int action, int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					switch (action)
					{
						case GLFW_PRESS:
						{
							Event::MouseButtonPressedEvent event(button);
							data.callback(event);
							break;
						}
						case GLFW_RELEASE:
						{
							Event::MouseButtonReleasedEvent event(button);
							data.callback(event);
							break;
						}
					}
				});

				glfwSetScrollCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, double xOffset, double yOffset)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					Event::MouseScrolledEvent event((float)xOffset, (float)yOffset);
					data.callback(event);
				});

				glfwSetCursorPosCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, double x, double y)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

					Event::MouseMovedEvent event((float)x, (float)y);
					data.callback(event);
				});
			}

			GLFWWindow::~GLFWWindow()
			{
				glfwDestroyWindow((GLFWwindow*)windowHandle);
				Engine::Core::Log::LogLine() << "GLFW window is closing";
			}

			void GLFWWindow::Update()
			{
				glfwSwapBuffers((GLFWwindow*)windowHandle);
				glfwPollEvents();
			}

			void GLFWWindow::SetEventCallback(std::function<void(Event::Event&)> callback)
			{
				this->windowData.callback = callback;
			}
		}
	}
}


