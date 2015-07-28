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
		static void Write(const std::string& text, const bool clean = false);
		static void Writeln(const std::string& text, const bool clean = false);
	};
	
}
