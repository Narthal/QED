#ifndef APPLICATION_H
#define APPLICATION_H

#include "../QEDApi.h"
#include "../Window/CoreWindow.h"
#include "../Event/WindowEvent.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerStack.h"

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Application
			{
				class QED_API Application
				{
				public:
					inline static Application& GetInstance()
					{
						static Application instance;
						return instance;
					}

					virtual ~Application() {};

					// Delete copy and move constructors and assign operators
					Application(Application const&) = delete;				// Copy construct
					Application(Application&&) = delete;					// Move construct
					Application& operator=(Application const&) = delete;	// Copy assign
					Application& operator=(Application&&) = delete;			// Move assign

					void Initialize();

					void OnEvent(Event::Event& event);

					void RunMainLoop();

					void PushLayer(Layer::Layer* layer);
					void PushOverlay(Layer::Layer* overlay);

					inline Window::CoreWindow* GetWindow() { return window; }

					bool OnWindowClose(Event::WindowCloseEvent& event);



				private:
					// Singleton istance
					Application() { Initialize(); }

					bool isRunning;
					Window::CoreWindow* window;
					Layer::LayerStack layerStack;



				};
			}
		}
	}
}

#endif // !APPLICATION_H
