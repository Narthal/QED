#ifndef INPUT_H
#define INPUT_H

#include "../Core/QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Input
		{
			class QED_API CoreInput
			{			
			public:
				static CoreInput& GetInstance();
				// Keyboard
				inline static bool IsKeyPressed(int keycode) { return GetInstance().IsKeyPressedImplementation(keycode); }

				// Mouse
				inline static bool IsMouseButtonPressed(int button) { return GetInstance().IsMouseButtonPressedImplementation(button); }
				inline static std::pair<float, float> GetMousePosition() { return GetInstance().GetMousePositionImplementation(); }
				inline static float GetMouseX() { return GetInstance().GetMouseXImplementation(); }
				inline static float GetMouseY() { return GetInstance().GetMouseYImplementation(); }

			protected:
				// Keyboard implementation
				virtual bool IsKeyPressedImplementation(int keycode) = 0;

				// Mouse implementation
				virtual bool IsMouseButtonPressedImplementation(int button) = 0;
				virtual std::pair<float, float> GetMousePositionImplementation() = 0;
				virtual float GetMouseXImplementation() = 0;
				virtual float GetMouseYImplementation() = 0;
			};
		}
	}
}


#endif // !INPUT_H