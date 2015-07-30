#pragma once

#include <string>


#ifndef OC_FUNCTION_NAME
#ifdef WIN32   // WINDOWS
#define OC_FUNCTION_NAME  __FUNCTION__  
#else          // *NIX
#define OC_FUNCTION_NAME   __func__ 
#endif
#endif

#define AppContext ( OpenClouds::GetFilename(__FILE__) + "@" + OC_FUNCTION_NAME + ":" + std::to_string(__LINE__))
#define ClassName  (typeid(*this).name())
namespace OpenClouds
{
	std::string GetFilename(const char* fn);
}