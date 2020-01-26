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
				layers.emplace(layers.begin() + insertIndex, layer);
				insertIndex++;
				layer->OnAttach();
			}

			void LayerStack::PushOverlay(Layer* overlay)
			{
				layers.emplace_back(overlay);
				overlay->OnAttach();
			}


			void LayerStack::PopLayer(Layer* layer)
			{
				auto it = std::find(layers.begin(), layers.begin() + insertIndex, layer);
				if (it != layers.end())
				{
					layer->OnDetach();
					layers.erase(it);
					insertIndex--;
				}
			}

			void LayerStack::PopOverlay(Layer* overlay)
			{
				auto it = std::find(layers.begin() + insertIndex, layers.end(), overlay);
				if (it != layers.end())
				{
					overlay->OnDetach();
					layers.erase(it);
				}
			}
		}
	}
}
