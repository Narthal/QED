#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "Module/QEDApi.h"

#include "Layer.h"


namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			class QED_ENGINE_API LayerStack
			{
			public: // Ctor / Dtor
				LayerStack() = default;
				~LayerStack();

			public: // Push / Pop layer
				void PushLayer(Layer* layer);
				void PushOverlay(Layer* overlay);
				void PopLayer(Layer* layer);
				void PopOverlay(Layer* overlay);

			public: // Iterator interface
				// Must be lower case so it maches std implementation of iterator
				std::vector<Layer*>::iterator begin() { return layers.begin(); }
				std::vector<Layer*>::iterator end() { return layers.end(); }

			private:
				std::vector<Layer*> layers;
				unsigned int insertIndex = 0;
			};
		}
	}
}



#endif // !LAYER_STACK_H
