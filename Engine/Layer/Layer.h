#ifndef LAYER_H
#define LAYER_H

#include "../Event/Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			class Layer
			{
			public:
				Layer(const std::string& name) : name(name) {}
				virtual ~Layer() {}

				virtual void OnAttach() {}
				virtual void OnDetach() {}
				virtual void OnUpdate() {}
				virtual void OnEvent(Event::Event& event) {}

				inline const std::string& GetName() const { return name; }

			protected:
				std::string name;
			};
		}
	}
}



#endif // !LAYER_H
