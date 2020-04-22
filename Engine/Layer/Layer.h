#ifndef LAYER_H
#define LAYER_H

#include "../Module/QEDApi.h"
#include "../Module/Interfaces/ModuleInterface.h"
#include "../Event/Event.h"
#include "../Core/Time/TimeStep.h"

namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			class QED_ENGINE_API Layer : public Module::Interfaces::ModuleInterface
			{
			public: // Ctor / Dtor
				Layer(const char* name = "layer", const bool isUI = false);
				virtual ~Layer() = 0;
				virtual void Initialize() override;

			public: // Layer events
				virtual void OnAttach() {}
				virtual void OnDetach() {}
				virtual void OnUpdate(Core::Time::TimeStep timeStep) {}
				virtual void OnUIRender() {}
				virtual void OnEvent(Event::Event& event) {}

			public: // Utility
				inline const char* GetLayerName() const { return name; }

			public: // Get / Set
				bool IsUI() { return isUI; }

			protected:
				bool isUI;
				const char* name;
			};
		}
	}
}



#endif // !LAYER_H
