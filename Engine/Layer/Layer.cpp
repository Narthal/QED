#include "EnginePCH.h"
#include "Layer.h"

#include "../Core/Application/Application.h"

namespace QED
{
	namespace Engine
	{
		namespace Layer
		{
			Layer::Layer(const char* name, const bool isUI) : name(name), isUI(isUI) {}

			void Layer::Initialize()
			{
				Core::Application::Application& app = Core::Application::Application::GetInstance();
				app.PushLayer(this);

			}

			Layer::~Layer() {}
		}
	}
}