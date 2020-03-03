#ifndef LAYER_H
#define LAYER_H

#include "../Core/QEDApi.h"
#include "../Event/Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			class QED_API Layer
			{
				public:
				Layer(const std::string& name = "layer", const bool isUI = false) : name(name), isUI(isUI) {}
				virtual ~Layer() {}

				virtual void OnAttach() {}
				virtual void OnDetach() {}
				virtual void OnUpdate() {}
				virtual void OnUIRender() {}
				virtual void OnEvent(Event::Event& event) {}

				inline const std::string& GetName() const { return name; }

				bool IsUI() { return isUI; }

				protected:
				bool isUI;

			protected:
				std::string name;
			};
		}
	}
}



#endif // !LAYER_H
