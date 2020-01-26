#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "Layer.h"


namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			class LayerStack
			{
			public:
				LayerStack() = default;
				~LayerStack();

				void PushLayer(Layer* layer);
				void PushOverlay(Layer* overlay);
				void PopLayer(Layer* layer);
				void PopOverlay(Layer* overlay);

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
