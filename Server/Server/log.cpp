#include <iostream>
#include <ctime>

#include "Log.h"

namespace OpenClouds
{
	std::string Log::appName = "OpenClouds";

	void Log::Write(const std::string& text, const LogType lt, const bool clean)
	{
		
		if (!clean)
		{
			// SET CONSOLE COLOR TO GREEN

			std::cout << "[" << appName << "] ";
			time_t t = time(0); // get time now
			struct tm now;
			localtime_s(&now, &t);
			std::cout << (now.tm_year + 1900) << '/'
				<< (now.tm_mon + 1) << '/'
				<< now.tm_mday << "-"
				<< now.tm_hour << ":"
				<< now.tm_min << ":";

			// SET CONSOLE COLOR TO LIGHT GRAY

			std::cout << now.tm_sec << "   >>   ";
		}

		switch (lt)
		{
		case(Normal) :
			// SET CONSOLE COLOR TO LIGHT GRAY
			break;
		case(Warning) :
			// SET CONSOLE COLOR TO YELLOW
			break;
		case(Error) :
			// SET CONSOLE COLOR TO RED
			break;
		case(Good) :
			// SET CONSOLE COLOR TO GREEN
			break;
		}

		
		std::cout << text;


		// RESET CONSOLE COLOR TO LIGHT GRAY

	}
	void Log::Write(const std::string& text, const LogType lt)
	{
		Log::Write(text, lt, false);
	}
	void Log::Write(const std::string& text)
	{
		Log::Write(text, LogType::Normal, false);
	}

	void Log::Writeln(const std::string& text, const LogType lt, const bool clean)
	{
		Log::Write(text + "\n", lt, clean);
	}
	void Log::Writeln(const std::string& text, const LogType lt)
	{
		Log::Write(text + "\n", lt, false);
	}
	void Log::Writeln(const std::string& text)
	{
		Log::Write(text + "\n", LogType::Normal, false);
	}


}