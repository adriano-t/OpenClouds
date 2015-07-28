#pragma once

#include <string>


#ifndef OC_FUNCTION_NAME
#ifdef WIN32   //WINDOWS
#define OC_FUNCTION_NAME  __FUNCTION__  
#else          //*NIX
#define OC_FUNCTION_NAME   __func__ 
#endif
#endif

#define GetContext() ( GetCodeFilename(__FILE__) + std::string("@") + std::string(OC_FUNCTION_NAME) + std::string(":") + OpenClouds::GetCodeLine(__LINE__))

namespace OpenClouds
{
	std::string GetCodeLine(long line);
	std::string GetCodeFilename(char* fn);
}