#include "EnginePCH.h"
#include "ImGuiLayer.h"
#undef new

#include "../Core/Application/Application.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

// HACK: temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace QED
{
	namespace Engine
	{
		namespace UI
		{
			ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer", true) {}

			ImGuiLayer::~ImGuiLayer()
			{
				ImGui::DestroyContext();
			}

			void ImGuiLayer::OnAttach()
			{
				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
				io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
				//io.ConfigViewportsNoAutoMerge = true;
				//io.ConfigViewportsNoTaskBarIcon = true;

				// Setup Dear ImGui style
				ImGui::StyleColorsDark();
				//ImGui::StyleColorsClassic();

				// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
				ImGuiStyle& style = ImGui::GetStyle();
				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				{
					style.WindowRounding = 0.0f;
					style.Colors[ImGuiCol_WindowBg].w = 1.0f;
				}

				// Get Application
				Core::Application::Application& app = Core::Application::Application::GetInstance();
				// Get GLFW window
				GLFWwindow* windowHandle = (GLFWwindow*)app.GetWindow()->GetWindowHandle();

				// Set up platform / renderer bindings
				ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
				ImGui_ImplOpenGL3_Init("#version 410");
			}

			void ImGuiLayer::OnDetach()
			{
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplGlfw_Shutdown();
				ImGui::DestroyContext();
			}

			void ImGuiLayer::OnUIRender()
			{
				static bool show = true;
				ImGui::ShowDemoWindow(&show);
			}

			void ImGuiLayer::Begin()
			{
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();
			}

			void ImGuiLayer::End()
			{
				// Get ImGui io
				ImGuiIO& io = ImGui::GetIO();
				// Get Application
				Core::Application::Application& app = Core::Application::Application::GetInstance();
				// Set display size in io
				io.DisplaySize = ImVec2((float)app.GetInstance().GetWindow()->GetWidth(), (float)app.GetInstance().GetWindow()->GetHeight());

				// Rendering
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				{
					GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					glfwMakeContextCurrent(backupCurrentContext);
				}
			}
		}
	}
}

#define new DEBUG_NEW