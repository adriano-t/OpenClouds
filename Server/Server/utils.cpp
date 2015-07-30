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