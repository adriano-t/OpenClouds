#pragma once

#ifndef OC_FUNCTION_NAME
#ifdef WIN32   //WINDOWS
#define OC_FUNCTION_NAME  __FUNCTION__  
#else          //*NIX
#define OC_FUNCTION_NAME   __func__ 
#endif
#endif


namespace OpenClouds
{

	std::string GetContext()
	{
		std::string res = __FILE__;
		res += ":";
		res += __LINE__;
		res += " @";
		res += OC_FUNCTION_NAME;
		return(res);
	}
}