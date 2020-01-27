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

				virtual void OnAttach() override;
				virtual void OnDetach() override;
				virtual void OnUIRender() override;

				void Begin();
				void End();

			private:
				float time = 0.0f;
			};
		}
	}
}


#endif // !IMGUI_LAYER_H
