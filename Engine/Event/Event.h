#ifndef EVENT_H
#define EVENT_H


// TODO: move to utils or smg
#define BIT(x) 1 << x

namespace QED
{
	namespace Engine
	{
		namespace Event
		{
			enum class EventType
			{
				/* Not used	*/	None,
				/* Window	*/	WindowOpen, WindowClose, WindowResize, WindowGotFocus, WindowLostFocus, WindowMoved,
				/* App		*/	ApplicationTick,
				/* Render	*/	Render,
				/* Entity	*/	EntityTick, EntityBegin,
				/* Keyboard */	KeyPressed, KeyReleased,
				/* Mouse	*/	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
			};

			enum class EventCategory
			{
				None = 0,
				Window = BIT(0),
				Application = BIT(1),
				Render = BIT(2),
				Entity = BIT(3),
				Keyboard = BIT(4),
				Mouse = BIT(5),
			};


			//TODO: move macros
			#define EVENT_CLASS_TYPE(type)															\
			static EventType GetStaticType() { return EventType::type; }							\
			virtual EventType GetEventType() const override { return GetStaticType(); }				\
			virtual const char* GetName() const override { return #type; }

			#define EVENT_CLASS_CATEGORY(category)													\
			virtual int GetCategoryFlags() const override { return (int)EventCategory::category; }



			class Event
			{
			public:
				virtual EventType GetEventType() const = 0;
				virtual const char* GetName() const = 0;
				virtual int GetCategoryFlags() const = 0;
				virtual std::string ToString() const { return GetName(); }

				inline bool IsInCategory(EventCategory eventCategory)
				{
					return GetCategoryFlags() & (int)eventCategory;
				}

			protected:
				bool handled = false;

			private:

			};

			class EventDispatcher
			{
			public:
				EventDispatcher(Event& event) : event(event) {}

				// F will be deduced by the compiler
				template<typename T, typename F>
				bool Dispatch(const F& func)
				{
					if (event.GetEventType() == T::GetStaticType())
					{
						event.Handled = func(static_cast<T&>(event));
						return true;
					}
					return false;
				}
			private:
				Event& event;
			};

			inline std::ostream& operator<<(std::ostream& os, const Event& e)
			{
				return os << e.ToString();
			}
		}
	}
}



#endif // !EVENT_H
