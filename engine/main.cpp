


#include "Log.hpp"


int main()
{

	QED::Common::Log::LogLine() << "LogLine " << 4 << " the win...." << QED::Common::Log::Severity::Error;


	return 0;
}