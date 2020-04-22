#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "Module/QEDApi.h"
#include "Event/Event.h"

// Renderer
#include "Graphics/Interface/API/Context.h"

#include "Core/Type/Type.h"

namespace QED
{
	namespace Engine
	{
		namespace Window
		{
			enum class ContextType
			{
				None,
				OpenGL,
				Other
			};

			struct WindowData
			{
				// Basic properties
				int width = 0;
				int height = 0;
				bool isVsync = true;
				bool isFullscreen = false;

				// Event callback
				std::function<void(Event::Event&)> callback = nullptr;
			};

			class QED_ENGINE_API CoreWindow
			{
			public: // Ctor / Dtor
				CoreWindow(int width = 1280, int height = 720, bool isVsync = true, bool isFullscreen = false)
				{
					windowData.width = width;
					windowData.height = height;
					windowData.isVsync = isVsync;
					windowData.isFullscreen = isFullscreen;
				}

				virtual ~CoreWindow() {};

			public: // Window events
				virtual void OnUpdate() = 0;

			public: // Callback setters
				virtual void SetEventCallback(std::function<void(Event::Event&)> callback) = 0;

			public: // Get
				inline int GetWidth() const { return windowData.width; }
				inline int GetHeight() const { return windowData.height; }

				virtual void* GetWindowHandle() const = 0;

			protected:
				// Basic data
				WindowData windowData;
				Scope<Graphics::Interface::API::Context> context;

				// Window implementation
				void* windowHandle = nullptr;
				ContextType contextType = ContextType::None;
				
			};
		}
	}
}



#endif // !CORE_WINDOW_H
