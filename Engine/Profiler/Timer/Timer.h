#ifndef TIMER_H
#define TIMER_H

#include "Module/QEDApi.h"





namespace QED
{
	namespace Engine
	{
		namespace Profiler
		{
			struct ProfileResult
			{
				const char* name;
				float time;
			};

			class QED_ENGINE_API Timer
			{
			public:
				Timer(const char* name, std::function<void(ProfileResult)> callback);
				void Stop();
				~Timer();

			private:
				const char* name;
				std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
				bool isStopped = false;
				std::function<void(ProfileResult)> callback;
			};
		}
	}
}

#endif // !TIMER_H
