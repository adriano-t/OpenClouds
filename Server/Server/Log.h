#pragma once

#include <stdlib.h>
#include <string>


namespace OpenClouds
{
	class Log
	{
	private:
		static std::string appName;
	public:
		enum LogType
		{
			Normal, Warning, Error, Good
		};
		static void Write(const std::string& text, const LogType lt, const bool clean);
		static void Write(const std::string& text, const LogType lt);
		static void Write(const std::string& text);

		static void Writeln(const std::string& text, const LogType lt, const bool clean);
		static void Writeln(const std::string& text, const LogType lt);
		static void Writeln(const std::string& text);
	};

	
	
	
}
