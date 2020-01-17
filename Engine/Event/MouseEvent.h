#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.h"



namespace QED
{
	namespace Engine
	{
		namespace Event
		{
			class MouseMovedEvent : public Event
			{
			public:
				MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}

				inline float GetX() const { return mouseX; }
				inline float GetY() const { return mouseY; }

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
					return ss.str();
				}

				EVENT_CLASS_TYPE(MouseMoved)
				EVENT_CLASS_CATEGORY(Mouse)
			private:
				float mouseX, mouseY;
			};

			class MouseScrolledEvent : public Event
			{
			public:
				MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

				inline float GetXOffset() const { return xOffset; }
				inline float GetYOffset() const { return yOffset; }

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
					return ss.str();
				}

				EVENT_CLASS_TYPE(MouseScrolled)
				EVENT_CLASS_CATEGORY(Mouse)
			private:
				float xOffset, yOffset;
			};

			class MouseButtonEvent : public Event
			{
			public:
				inline int GetMouseButton() const { return button; }

				EVENT_CLASS_CATEGORY(Mouse)
			protected:
				MouseButtonEvent(int button) : button(button) {}

				int button;
			};

			class MouseButtonPressedEvent : public MouseButtonEvent
			{
			public:
				MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "MouseButtonPressedEvent: " << button;
					return ss.str();
				}

				EVENT_CLASS_TYPE(MouseButtonPressed)
			};

			class MouseButtonReleasedEvent : public MouseButtonEvent
			{
			public:
				MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

				std::string ToString() const override
				{
					std::stringstream ss;
					ss << "MouseButtonReleasedEvent: " << button;
					return ss.str();
				}

				EVENT_CLASS_TYPE(MouseButtonReleased)
			};
		}
	}
}
#endif // !MOUSE_EVENT_H
