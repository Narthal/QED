#ifndef LOG_H
#define LOG_H


#pragma warning(push, 0)

#pragma warning(disable : 6387)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)
#pragma warning(disable : 6385)
#pragma warning(disable : 26451)

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#pragma warning(pop)

#include "Module/QEDApi.h"
#include "Core/Type/Reference.h"



// Core log macros
#define QED_CORE_LOG_TRACE(...)	::QED::Engine::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QED_CORE_LOG_INFO(...)	::QED::Engine::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QED_CORE_LOG_WARN(...)	::QED::Engine::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QED_CORE_LOG_ERROR(...)	::QED::Engine::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QED_CORE_LOG_FATAL(...)	::QED::Engine::Core::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define QED_CLIENT_LOG_TRACE(...)	::QED::Engine::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QED_CLIENT_LOG_INFO(...)	::QED::Engine::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define QED_CLIENT_LOG_WARN(...)	::QED::Engine::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QED_CLIENT_LOG_ERROR(...)	::QED::Engine::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define QED_CLIENT_LOG_FATAL(...)	::QED::Engine::Core::Log::GetClientLogger()->fatal(__VA_ARGS__)

// Asserts
#ifdef QED_ENABLE_ASSERTS
	#define QED_CLIENT_ASSERT(x, ...) { if(!(x)) { QED_CLIENT_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QED_CORE_ASSERT(x, ...) { if(!(x)) { QED_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QED_ASSERT(x, ...)
	#define QED_CORE_ASSERT(x, ...)
#endif

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			class QED_ENGINE_API Log
			{
				enum class Tag
				{
					Info,
					Debug,
					Warning,
					Error
				};

			public:

				static void Initialize();

				inline static Ref<spdlog::logger>& GetCoreLogger() { return coreLogger; }
				inline static Ref<spdlog::logger>& GetClientLogger() { return clientLogger; }

			private:

			#pragma warning(push, 0)
			// class std::shared_ptr<spdlog::logger> needs to have dll - interface to be used by clients of class Log
			// Not needed as highest level of class usage stops at Log, no instances are created from log lib
			#pragma warning(disable : 4251)
				static Ref<spdlog::logger> coreLogger;
				static Ref<spdlog::logger> clientLogger;
			#pragma warning(pop)
			};
		}
	}
}


#endif // !LOG_H
