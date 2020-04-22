#ifndef CONTEXT_H
#define CONTEXT_H

#include "Module/QEDApi.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace API
				{
					class QED_ENGINE_API Context
					{
					public:
						// Initialize context
						// NOTE: Owner should call this after constructor
						virtual void Init() = 0;

						virtual void SwapBuffers() = 0;
					};
				}
			}
		}
	}
}



#endif // !CONTEXT_H
