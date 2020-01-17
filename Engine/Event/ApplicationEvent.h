#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Event
		{

			class AppTickEvent : public Event
			{
			public:
				AppTickEvent() = default;

				EVENT_CLASS_TYPE(ApplicationTick)
				EVENT_CLASS_CATEGORY(Application)
			};
		}
	}
}


#endif // !APPLICATION_EVENT_H
