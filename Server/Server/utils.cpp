#include <string>

#include "Utils.h"


namespace OpenClouds
{
	std::string IToS(long p)
	{
		char* buff = new char[40];
		_itoa_s((int)p, buff, 40, 10);
		std::string line(buff);
		return(line);
	}

	std::string GetFilename(const char* p)
	{
		std::string fn = p;
		std::size_t pos = fn.find_last_of("/\\");
		return fn.substr(pos + 1);
	}


}