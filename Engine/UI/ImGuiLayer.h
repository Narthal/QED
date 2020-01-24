#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "../Core/QEDApi.h"
#include "../Layer/Layer.h"

#include "../Event/MouseEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/WindowEvent.h"

namespace QED
{
	namespace Engine
	{
		namespace UI
		{
			class QED_API ImGuiLayer : public Layer::Layer
			{
			public:
				ImGuiLayer();
				~ImGuiLayer();

				void OnAttach() override;
				void OnDetach() override;
				void OnUpdate() override;
				void OnEvent(Event::Event& event) override;

			private:
				float time = 0.0f;

			private:
				// Mouse events
				bool OnMouseButtonPressedEvent(Event::MouseButtonPressedEvent& event);
				bool OnMouseButtonReleasedEvent(Event::MouseButtonReleasedEvent& event);
				bool OnMouseScrolledEvent(Event::MouseScrolledEvent& event);
				bool OnMouseMovedEvent(Event::MouseMovedEvent& event);

				// Keyboar events
				bool OnKeyPressedEvent(Event::KeyPressedEvent& event);
				bool OnKeyReleasedEvent(Event::KeyReleasedEvent& event);
				bool OnKeyTypedEvent(Event::KeyTypedEvent& event);

				// Window events
				bool OnWindowResizedEvent(Event::WindowResizeEvent& event);
			};
		}
	}
}


#endif // !IMGUI_LAYER_H
