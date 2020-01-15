#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime> 




namespace QED
{
	namespace Common
	{
		namespace Log
		{
			#pragma region Severity

			#define SEVERITY	\
				X(Info)			\
				X(Debug)		\
				X(Error)

			enum class Severity
			{
				#define X(value) value,
				SEVERITY
				#undef X
			};

			const char* GetSeverityString(Severity s)
			{
				switch (s)
				{
					#define X(value) case Severity::value: return #value;
					SEVERITY
					#undef X
				default: return "";
				}
			}

			#pragma endregion

			enum class Tags
			{
				Time,
			};

			const char* GetTime()
			{
				auto time = std::chrono::system_clock().now();
				std::time_t timeT = std::chrono::system_clock::to_time_t(time);
				return std::ctime(&timeT);

			}

			class LogLine
			{
			public:
				LogLine(Severity severity = Severity::Info, std::ostream& outStream = std::cout) : outStream(outStream), severity(severity) {}
				~LogLine()
				{
					// Severity
					stringStreamBuffer << '[' << GetSeverityString(severity) << ']';

					// Tags


					stringStreamBuffer << "\n";
					outStream << stringStreamBuffer.rdbuf();
					outStream.flush();
				}

				// Handle basic types
				template <class T>
				LogLine& operator<<(const T& thing) { stringStreamBuffer << thing; return *this; }

				// Handle severity
				LogLine& operator<<(const Severity& severity) { this->severity = severity; return *this; }

				// Handle tags
				LogLine& operator<<(const Tags& tag) { this->tags.emplace_back(tag); return *this; }

			private:
				std::stringstream stringStreamBuffer;
				std::ostream& outStream;
				
				Severity severity;
				std::vector<Tags> tags;
				//static LogFilter...
			};
		}
	}
}


#endif // !LOG_H
