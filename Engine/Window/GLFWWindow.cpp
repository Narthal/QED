#include "EnginePCH.h"
#include "GLFWWindow.h"


// GLFW
#include "GLFW/glfw3.h"



// Renderer
#include "Graphics/OpenGL/API/OpenGLContext.h"

// Engine utils
#include "Core/Log/Log.h"

// Events
#include "Event/Event.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

// Profiler
#include "Profiler/Instrumentor.h"




namespace QED
{
	namespace Engine
	{
		namespace Window
		{
			GLFWWindow::GLFWWindow()
			{
				QED_PROFILE_FUNCTION();

				// Initialize GLFW
				bool success = glfwInit();
				if (!success)
				{
					QED_CORE_ASSERT(success, "GLFW failed to initialize");

					// TODO: set glfw error callback
					//glfwSetErrorCallback()
				}

				glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

				// Create window
				windowHandle = glfwCreateWindow(1280, 720, "My Title", NULL, NULL);
				glfwMakeContextCurrent((GLFWwindow*)windowHandle);
				glfwSetWindowUserPointer((GLFWwindow*)windowHandle, &windowData);

				// Disable VSync
				if (windowData.isVsync)
				{
					// TODO: fix VSync 
					glfwSwapInterval(1);
				}
				else
				{
					glfwSwapInterval(0);
				}
			

				// Create context
				context = Core::Type::CreateScope<Graphics::OpenGL::API::OpenGLContext>((GLFWwindow*)windowHandle);
				context->Init();



				#pragma region SetGLFWCallbacks

				// Set GLFW error callback
				glfwSetErrorCallback([](int error, const char* msg)
				{
						QED_CORE_LOG_ERROR("GLFW error : {0} {1}", error, msg);
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

				// Set key typed event
				glfwSetCharCallback((GLFWwindow*)windowHandle, [](GLFWwindow* handle, unsigned int keycode)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
					Event::KeyTypedEvent event(keycode);
					data.callback(event);
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

				#pragma endregion
			}

			GLFWWindow::~GLFWWindow()
			{
				QED_PROFILE_FUNCTION();

				context.release();
				glfwDestroyWindow((GLFWwindow*)windowHandle);
				QED_CORE_LOG_INFO("GLFW window is closing");
			}

			void GLFWWindow::OnUpdate()
			{
				QED_PROFILE_FUNCTION();

				glfwPollEvents();
				context->SwapBuffers();
			}

			void GLFWWindow::SetEventCallback(std::function<void(Event::Event&)> callback)
			{
				this->windowData.callback = callback;
			}
		}
	}
}


