#include <string>

#include "Utils.h"


namespace OpenClouds
{
	std::string GetFilename(const char* p)
	{
		std::string fn = p;
		std::size_t pos = fn.find_last_of("/\\");
		return fn.substr(pos + 1);
	}
}

#if OC_OS_WINDOWS
#include <windows.h>
//-----------------------------------------------------------------------------
void setcolor(int textcol)
{
	textcol %= 16;
	unsigned short wAttributes = (unsigned)textcol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
}
void setcolor(OpenClouds::ConsoleColor col)
{
	setcolor((int)col);
}
#endif

namespace OpenClouds
{
	void SetConsoleColor(OpenClouds::ConsoleColor Col)
	{
		setcolor(Col);
	}
}