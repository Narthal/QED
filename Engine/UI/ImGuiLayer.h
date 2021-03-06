#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "../Module/QEDApi.h"
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
			class QED_ENGINE_API ImGuiLayer : public Layer::Layer
			{
			public: // Ctor / Dtor / Init
				ImGuiLayer();
				~ImGuiLayer();
				inline void Initialize() override {};

			public: // Layer events
				virtual void OnAttach() override;
				virtual void OnDetach() override;

			public: // UI
				void Begin();
				void End();

			public: // Utility
				// Define name as imguiLayer is inheriting from module interface
				const char* GetName() const override { return "ImGuiLayerInterface"; }

			private:
				float time = 0.0f;
			};
		}
	}
}


#endif // !IMGUI_LAYER_H
