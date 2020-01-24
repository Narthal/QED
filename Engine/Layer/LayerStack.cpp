#include "EnginePCH.h"
#include "LayerStack.h"





namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			LayerStack::~LayerStack()
			{
				for (Layer* layer : layers)
				{
					delete layer;
				}
			}

			void LayerStack::PushLayer(Layer* layer)
			{
				layerInsert = layers.emplace(layerInsert, layer);
				layer->OnAttach();
			}

			void LayerStack::PushOverlay(Layer* overlay)
			{
				layers.emplace_back(overlay);
				overlay->OnAttach();
			}


			void LayerStack::PopLayer(Layer* layer)
			{
				auto it = std::find(layers.begin(), layers.end(), layer);
				if (it != layers.end())
				{
					layers.erase(it);
					layerInsert--;
				}
			}

			void LayerStack::PopOverlay(Layer* overlay)
			{
				auto it = std::find(layers.begin(), layers.end(), overlay);
				if (it != layers.end())
				{
					layers.erase(it);
				}
			}
		}
	}
}
