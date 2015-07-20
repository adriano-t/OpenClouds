#pragma once
#ifndef OC_LOG_H
#define OC_LOG_H

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

#endif // OC_LOG_H