#pragma once

#include <string>
#include "Log.h"

namespace OpenClouds
{

	class Exception
	{
		std::string errMessage;
		std::string errContext;
		Exception* nestedException;

		void printST()
		{

		}
	public:
		Exception()
		{
			errContext = "";
			errMessage = "";
			nestedException = nullptr;
		}

		Exception(const std::string errContext) 
			: Exception()
		{
			this->errContext = errContext;
		}

		Exception(const std::string errContext, const std::string errMessage)
			: Exception(errContext)
		{
			this->errMessage = errMessage;
		}

		Exception(const std::string errContext, const std::string errMessage, 
			Exception* nestedException) : Exception(errContext, errMessage)
		{
			this->nestedException = nestedException;
		}

		void PrintStackTrace()
		{
			Exception* ptr = this;
			std::string header = "";
			std::string className;

			while (ptr != nullptr)
			{
				className = typeid(*ptr).name();

				if (ptr->errContext.length > 0)
					Log::Write(header + "Exception occurred.\n" + className + " in [" + 
					ptr->errContext + "]: ", true);
				else
					Log::Write(header + "Exception occurred.\n" + className +
					" in [unknown context]: ", true);

				if (ptr->errMessage.length > 0)
					Log::Write(header + ptr->errMessage, true);
				else
					Log::Write(header + "no error message.", true);

				ptr = ptr->nestedException;
				header += "\t\t";
			}
		}
	};

	class IndexOutOfBound : Exception
	{
	public:
		IndexOutOfBound() : Exception() {};
	};

	class BadRealloc : Exception
	{
	public:
		BadRealloc() : Exception() {};
		BadRealloc(std::string errContext) : Exception(errContext) {};
		BadRealloc(std::string errContext, std::string errMsg) : Exception(errContext, errMsg) {};
		BadRealloc(std::string errContext, std::string errMsg, Exception* nestedException) 
			: Exception(errContext, errMsg, nestedException) {};
	};
	enum class BufferSeek{
		Start, Relative, End
	};
}
