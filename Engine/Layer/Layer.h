#ifndef LAYER_H
#define LAYER_H

#include "../Module/QEDApi.h"
#include "../Module/Interfaces/ModuleInterface.h"
#include "../Event/Event.h"


namespace QED
{
	namespace Engine
	{
		namespace Layer
		{


			class QED_ENGINE_API Layer : public Module::Interfaces::ModuleInterface
			{
				public:
				Layer(const char* name = "layer", const bool isUI = false);
				virtual ~Layer() = 0;

				virtual void OnAttach() {}
				virtual void OnDetach() {}
				virtual void OnUpdate() {}
				virtual void OnUIRender() {}
				virtual void OnEvent(Event::Event& event) {}

				inline const char* GetLayerName() const { return name; }

				bool IsUI() { return isUI; }

				protected:
				bool isUI;

				public:
				virtual void Initialize() override;

			protected:
				const char* name;
			};
		}
	}
}



#endif // !LAYER_H
