#pragma once

#include <string>

#ifndef OC_OS
#ifdef WIN32
#define OC_OS_WINDOWS 1
#elif
#define DC_OS_WINDOWS 0
#endif
#endif

#ifndef OC_FUNCTION_NAME
#if OC_OS_WINDOWS   // WINDOWS
#define OC_FUNCTION_NAME  __FUNCTION__  
#else          // *NIX
#define OC_FUNCTION_NAME   __func__ 
#endif
#endif


#define AppContext ( OpenClouds::GetFilename(__FILE__) + std::string("@") + std::string(OC_FUNCTION_NAME) + std::string(":") + OpenClouds::IToS(__LINE__))
#define ClassName  (typeid(*this).name())
namespace OpenClouds
{
	std::string IToS(long line);
	std::string GetFilename(const char* fn);

	enum ConsoleColor
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, dark_pink = 5, dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, cyan = 11,
		red = 12,
		purple = 13, pink = 13, magenta = 13,
		yellow = 14,
		white = 15
	};
	void SetConsoleColor(ConsoleColor col);
}