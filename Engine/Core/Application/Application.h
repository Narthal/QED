#ifndef APPLICATION_H
#define APPLICATION_H

#include "Module/QEDApi.h"
#include "Core/Type/Type.h"
#include "Module/Kernel.h"
#include "Module/QEDApi.h"
#include "Window/CoreWindow.h"
#include "Event/WindowEvent.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"
#include "UI/ImGuiLayer.h"

// Renderer
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/OrthographicCamera.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Application
			{
				class QED_ENGINE_API Application
				{
				protected:
					// Singleton istance
					Application() {};

				public:
					// Initialization code must be run after ctor and before other methods
					void Initialize();

					// Magic static singleton
					inline static Application& GetInstance()
					{
						static Application instance;
						return instance;
					}

					// Default destructor
					virtual ~Application() = default;
					
					// Delete copy and move constructors and assign operators
					Application(Application const&) = delete;				// Copy construct
					Application(Application&&) = delete;					// Move construct
					Application& operator=(Application const&) = delete;	// Copy assign
					Application& operator=(Application&&) = delete;			// Move assign

					// Event dispatcher
					void OnEvent(Event::Event& event);

					// Main loop executor
					void RunMainLoop();
				
					// Add layer to update stack
					void PushLayer(Layer::Layer* layer);
					// Add UI layer to update stack
					void PushOverlay(Layer::Layer* overlay);

					// Window GET
					inline Window::CoreWindow* GetWindow() { return window.get(); }

					// Run on event window close
					bool OnWindowClose(Event::WindowCloseEvent& event);

					bool OnWindowResize(Event::WindowResizeEvent& event);


				private:
					bool isRunning = false;
					Ref<Window::CoreWindow> window = nullptr;
					Layer::LayerStack layerStack;
					UI::ImGuiLayer* UILayer = nullptr;
					Module::Kernel* kernel = nullptr;
					float lastFrameTime = 0.0f;
					bool minimized = false;
				};
			}
		}
	}
}

#endif // !APPLICATION_H
