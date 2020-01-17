#ifndef KEY_EVENT_H
#define KEY_EVENT_H


#include "Event.h"

namespace QED
{
	namespace Engine
	{
		namespace Event
		{
			class KeyEvent : public Event
			{
			public:
				inline int GetKeyCode() const { return keyCode; }

				EVENT_CLASS_CATEGORY(Keyboard)
			protected:
				KeyEvent(int keycode)
					: keyCode(keycode) {}

				int keyCode;
			};

			class KeyPressedEvent : public KeyEvent
			{
			public:
				KeyPressedEvent(int keycode, int repeatCount)
					: KeyEvent(keycode), repeatCount(repeatCount) {}

				inline int GetRepeatCount() const { return repeatCount; }

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
					return ss.str();
				}

				EVENT_CLASS_TYPE(KeyPressed)
			private:
				int repeatCount;
			};

			class KeyReleasedEvent : public KeyEvent
			{
			public:
				KeyReleasedEvent(int keycode)
					: KeyEvent(keycode) {}

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "KeyReleasedEvent: " << keyCode;
					return ss.str();
				}

				EVENT_CLASS_TYPE(KeyReleased)
			};
		}
	}
}



#endif // !KEY_EVENT_H
