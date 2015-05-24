#pragma once
#ifndef ERROR_H
#define ERROR_H

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

namespace OpenClouds
{
	enum ErrorCode
	{
		INDEX_OUT_OF_RANGE
	};
	class Exception
	{
		ErrorCode err;
		std::string errMessage;
	public:
		Exception(ErrorCode ec);
		void AppendMessage(std::string& msg);

		//display error and exit from the program
		void Handle();
	};
}

#endif // ERROR_H
