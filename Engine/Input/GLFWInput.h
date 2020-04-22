#ifndef GLFW_INPUT_H
#define GLFW_INPUT_H



#include "CoreInput.h"

namespace QED
{
	namespace Engine
	{
		namespace Input
		{
			class GLFWInput : public CoreInput
			{
			public:
				// GLFW keyboard implementation
				virtual bool IsKeyPressedImplementation(int keycode) override;

				// GLFW mouse implementation
				virtual bool IsMouseButtonPressedImplementation(int button) override;
				virtual std::pair<float, float> GetMousePositionImplementation() override;
				virtual float GetMouseXImplementation() override;
				virtual float GetMouseYImplementation() override;
			};
		}
	}
}


#endif // !GLFW_INPUT_H
