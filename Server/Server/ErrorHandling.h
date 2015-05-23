#pragma once
#ifndef ERROR_H
#define ERROR_H

namespace OpenClouds
{
	enum ErrorCode
	{
		INDEX_OUT_OF_RANGE
	};
	class Exception
	{
	public:
		Exception();
		ErrorCode err;
	};
}

#endif // ERROR_H
