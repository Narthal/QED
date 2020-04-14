#include "EnginePCH.h"
#include "Timer.h"

#include "Core/Log/Log.h"

namespace QED
{
	namespace Engine
	{
		namespace Profiler
		{
			Timer::Timer(const char* name, std::function<void(ProfileResult)> callback) : name(name), callback(callback)
			{
				startTimePoint = std::chrono::high_resolution_clock::now();
			}

			void Timer::Stop()
			{
				auto endTimePoint = std::chrono::high_resolution_clock::now();

				long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
				long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			
				float diff = (end - start) * 0.001f;

				isStopped = true;

				//QED_CORE_LOG_INFO("{0} : {1}", name, diff);
				callback({name, diff});
			}

			Timer::~Timer()
			{
				if (!isStopped) Stop();
			}
		}
	}
}


