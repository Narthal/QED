#ifndef LOG_H
#define LOG_H

#define LOG std::cout

namespace QED
{
	namespace Engine
	{
		namespace Core
		{
			namespace Log
			{
				enum class Tag
				{
					Info,
					Debug,
					Warning,
					Error
				};
			}
		}
	}
}


#endif // !LOG_H
