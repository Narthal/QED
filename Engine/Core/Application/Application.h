#ifndef APPLICATION_H
#define APPLICATION_H



#include "../Module/Kernel.h"

#include "../Module/QEDApi.h"
#include "../Window/CoreWindow.h"
#include "../Event/WindowEvent.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerStack.h"
#include "../UI/ImGuiLayer.h"

// Renderer
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Application
			{
				class Application
				{
					protected:
					// Singleton istance
					Application() { }

					public:
					void Initialize();

					public:
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

					void OnEvent(Event::Event& event);

					void RunMainLoop();

					void PushLayer(Layer::Layer* layer);
					void PushOverlay(Layer::Layer* overlay);

					inline Window::CoreWindow* GetWindow() { return window.get(); }

					bool OnWindowClose(Event::WindowCloseEvent& event);


					private:
					bool isRunning = false;
					std::shared_ptr<Window::CoreWindow> window = nullptr;
					Layer::LayerStack layerStack;
					UI::ImGuiLayer* UILayer = nullptr;
					Module::Kernel* kernel = nullptr;

					std::shared_ptr<Graphics::VertexArray> vertexArray; 
					std::shared_ptr<Graphics::Shader> shader;

					std::shared_ptr<Graphics::VertexArray> squareVA;
					std::shared_ptr<Graphics::Shader> squareShader;
				};
			}
		}
	}
}

#endif // !APPLICATION_H
