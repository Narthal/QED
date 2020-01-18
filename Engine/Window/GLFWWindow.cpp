#include "EnginePCH.h"
#include "GLFWWindow.h"


// Log
#include "../Core/Log/Log.h"

QED::Engine::Window::GLFWWindow::GLFWWindow()
{
	glfwInit();
	windowHandle = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
}

QED::Engine::Window::GLFWWindow::~GLFWWindow()
{
	glfwDestroyWindow((GLFWwindow*)windowHandle);
	Engine::Core::Log::LogLine() << "GLFW window is closing";
}

void QED::Engine::Window::GLFWWindow::Update()
{
	glfwSwapBuffers((GLFWwindow*)windowHandle);
	glfwPollEvents();
}
