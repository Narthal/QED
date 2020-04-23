#ifndef RENDER_COMMAND_INTERFACE_H
#define RENDER_COMMAND_INTERFACE_H

#include "Module/QEDApi.h"

#include "Core/Type/Numeric.h"

namespace QED
{
	namespace Interface
	{
		namespace Graphics
		{
			namespace Renderer
			{
				class QED_ENGINE_API RenderCommand
				{
				public:
					static void SetClearColor(const Vec4& color);
					static void Clear();
				};
			}
		}
	}
}


#endif // !RENDER_COMMAND_INTERFACE_H
