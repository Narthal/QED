#include "EnginePCH.h"
#include "ImGuiLayer.h"

#include "../Core/Application/Application.h"

#include "imgui.h"
#include "ImGuiOpenGLRenderer.h"


// HACK: temporary
#include <GLFW\glfw3.h>
#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace UI
		{
			ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
			{

			}

			ImGuiLayer::~ImGuiLayer()
			{

			}

			void ImGuiLayer::OnAttach()
			{
				ImGui::CreateContext();
				ImGui::StyleColorsDark();

				ImGuiIO& io = ImGui::GetIO();
				io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
				io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

				// HACK:
				// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
				io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
				io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
				io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
				io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
				io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
				io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
				io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
				io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
				io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
				io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
				io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
				io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
				io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
				io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
				io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
				io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
				io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
				io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
				io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
				io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
				io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
				io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

				// OpenGL init
				ImGui_ImplOpenGL3_Init("#version 410");

			}

			void ImGuiLayer::OnDetach()
			{

			}

			void ImGuiLayer::OnUpdate()
			{
				ImGuiIO& io = ImGui::GetIO();
				Core::Application::Application& app = Core::Application::Application::GetInstance();
				io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());

				float glfwTime = (float)glfwGetTime();
				io.DeltaTime = time > 0.0f ? (glfwTime - time) : (1.0f / 60.0f);
				time = glfwTime;

				ImGui_ImplOpenGL3_NewFrame();
				ImGui::NewFrame();

				// Demo
				static bool show = true;
				ImGui::ShowDemoWindow(&show);



				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}

			void ImGuiLayer::OnEvent(Event::Event& event)
			{
				Event::EventDispatcher dispatcher(event);

				// Mouse events
				dispatcher.Dispatch<Event::MouseButtonPressedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnMouseButtonPressedEvent));
				dispatcher.Dispatch<Event::MouseButtonReleasedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnMouseButtonReleasedEvent));
				dispatcher.Dispatch<Event::MouseScrolledEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnMouseScrolledEvent));
				dispatcher.Dispatch<Event::MouseMovedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnMouseMovedEvent));
				
				// Keyboard events
				dispatcher.Dispatch<Event::KeyPressedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnKeyPressedEvent));
				dispatcher.Dispatch<Event::KeyReleasedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnKeyReleasedEvent));
				dispatcher.Dispatch<Event::KeyTypedEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnKeyTypedEvent));
				
				// Window events
				dispatcher.Dispatch<Event::WindowResizeEvent>(BIND_EVENT_FUCTION(UI::ImGuiLayer::OnWindowResizedEvent));
			}

			bool ImGuiLayer::OnMouseButtonPressedEvent(Event::MouseButtonPressedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.MouseDown[event.GetMouseButton()] = true;

				return false;
			}

			bool ImGuiLayer::OnMouseButtonReleasedEvent(Event::MouseButtonReleasedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.MouseDown[event.GetMouseButton()] = false;

				return false;
			}

			bool ImGuiLayer::OnMouseScrolledEvent(Event::MouseScrolledEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.MouseWheel += event.GetYOffset();
				io.MouseWheelH += event.GetXOffset();

				return false;
			}

			bool ImGuiLayer::OnMouseMovedEvent(Event::MouseMovedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.MousePos = ImVec2(event.GetX(), event.GetY());

				return false;
			}

			bool ImGuiLayer::OnKeyPressedEvent(Event::KeyPressedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.KeysDown[event.GetKeyCode()] = true;

				io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
				io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
				io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
				io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

				return false;
			}

			bool ImGuiLayer::OnKeyReleasedEvent(Event::KeyReleasedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.KeysDown[event.GetKeyCode()] = false;

				return false;
			}

			bool ImGuiLayer::OnKeyTypedEvent(Event::KeyTypedEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				
				int keycode = event.GetKeyCode();
				if (keycode > 0 && keycode < 0x10000)
				{
					io.AddInputCharacter((unsigned short)keycode);
				}

				return false;
			}

			bool ImGuiLayer::OnWindowResizedEvent(Event::WindowResizeEvent& event)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
				io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
				//Hack:
				glViewport(0.0f, 0.0f, event.GetWidth(), event.GetHeight());

				return false;
			}
		}
	}
}
