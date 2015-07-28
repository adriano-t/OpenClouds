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

		Exception(const std::string errMessage) 
			: Exception()
		{
			this->errMessage = errMessage;
		}

		Exception(const std::string errMessage, Exception* nestedException) 
			: Exception(errMessage)
		{
			this->nestedException = nestedException;
		}

		Exception(const std::string errContext, const std::string errMessage) 
			: Exception(errMessage)
		{
			this->errContext = errContext;
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
					Log::Write(header + "Exception occurred.\n" + className + " in [" + ptr->errContext + "]: ");
				else
					Log::Write(header + "Exception occurred.\n" + className + " in [unknown context]: ");

				if (ptr->errMessage.length > 0)
					Log::Write(header + ptr->errMessage);
				else
					Log::Write(header + "no error message.");

				ptr = ptr->nestedException;
				header += "\t\t";
			}
		}
	};

	class IndexOutOfBound : Exception
	{
	public:
		IndexOutOfBound() : Exception() {};
		IndexOutOfBound(const std::string errMessage) : Exception(errMessage) {};
		IndexOutOfBound(const std::string errMessage, Exception* nestedException) :
			Exception(errMessage, nestedException) {};
	};

	class BadRealloc : Exception
	{
	public:
		BadRealloc() : Exception() {};
		BadRealloc(const std::string errMessage) : Exception(errMessage) {};
		BadRealloc(const std::string errMessage, Exception* nestedException) :
			Exception(errMessage, nestedException) {};
	};
	enum class BufferSeek{
		Start, Relative, End
	};
}
