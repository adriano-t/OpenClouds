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
		static void Write(const std::string& text);
		static void Write(const std::string& tag, const std::string& text);
	};
	
}
