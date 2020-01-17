#ifndef	WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Event
		{
			class WindowResizeEvent : public Event
			{
			public:
				WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

				inline unsigned int GetWidth() const { return width; }
				inline unsigned int GetHeight() const { return height; }

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "WindowResizeEvent: " << width << ", " << height;
					return ss.str();
				}

				EVENT_CLASS_TYPE(WindowResize)
				EVENT_CLASS_CATEGORY(Window)
			private:
				unsigned int width, height;
			};

			class WindowCloseEvent : public Event
			{
			public:
				WindowCloseEvent() = default;

				EVENT_CLASS_TYPE(WindowClose)
				EVENT_CLASS_CATEGORY(Window)
			};
		}
	}
}


#endif // !WINDOW_EVENT_H
