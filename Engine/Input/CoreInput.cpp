#include "EnginePCH.h"
#include "CoreInput.h"

#include "GLFWInput.h"

namespace QED
{
	namespace Engine
	{
		namespace Input
		{
			CoreInput& CoreInput::GetInstance()
			{
				static GLFWInput instance;
				return instance;
			}
		}
	}
}


