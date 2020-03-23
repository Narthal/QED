#ifndef TIME_STEP_H
#define TIME_STEP_H

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Time
			{
				class TimeStep
				{
				public:
					TimeStep(float time) : time(time) {}

				public:
					inline const float GetSeconds() const { return time; }
					inline const float GetMiliseconds() const { return time * 1000; }

				public:
					operator float() const { return time; }
				private:
					float time;
				};
			}
		}
	}
}


#endif // !TIME_STEP_H

