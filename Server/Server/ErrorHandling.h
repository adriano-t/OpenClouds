#pragma once

#include <string>
#include "Log.h"
#include "Utils.h"

#include <iostream>

namespace OpenClouds
{

	class Exception
	{
	public:
		std::string className;
		std::string errMessage;
		std::string errContext;
		Exception* nestedException;
		Exception()
		{
			errContext = "";
			errMessage = "";
			className = typeid(*this).name();
			nestedException = nullptr;
		}

		Exception(const std::string className)
			: Exception()
		{
			this->className = className;
		}
		Exception(const std::string className, const std::string errContext) 
			: Exception(className)
		{
			this->errContext = errContext;
		}

		Exception(const std::string className, const std::string errContext, const std::string errMessage)
			: Exception(className, errContext)
		{
			this->errMessage = errMessage;
		}

		Exception(const std::string className, const std::string errContext, const std::string errMessage,
			Exception* nestedException) : Exception(className, errContext, errMessage)
		{
			this->nestedException = nestedException;
		}

		void PrintStackTrace()
		{
			Exception* ptr = this;
			std::string header = " ";
			std::string className;

			while (ptr != nullptr)
			{


				if (ptr->errContext.length() > 0)
					//Log::Writeln(header + "Exception " + ptr->className + " occurred in [" + 
					//ptr->errContext + "]: ", Log::Error, true);
					std::cout << header + "Exception " + ptr->className + " occurred in [" + ptr->errContext + "]: " << std::endl;
				else
					std::cout << header + "Exception " + ptr->className + " occurred in [unknown context]: " << std::endl;
					//Log::Writeln(header + "Exception " + ptr->className + 
					//" occurred in [unknown context]: ", Log::Error, true);

				if (ptr->errMessage.length() > 0)
					std::cout << "errMessage" << std::endl;
					//Log::Writeln(header + ptr->errMessage, Log::Error, true);
				else
					std::cout << header + "No error message." << std::endl;
					//Log::Writeln(header + "No error message.", Log::Error, true);

				ptr = ptr->nestedException;
				header += "  ";
			}
		}
	};

	class IndexOutOfBound : public Exception
	{
	public:
		IndexOutOfBound() : Exception(ClassName) {};
		IndexOutOfBound(const std::string errContext) : Exception(ClassName, errContext) {};
		IndexOutOfBound(const std::string errContext, const std::string errMsg)
			: Exception(ClassName, errContext, errMsg) {};
		IndexOutOfBound(const std::string errContext, const std::string errMsg, Exception* nestedException)
			: Exception(ClassName, errContext, errMsg, nestedException) {};
	};

	class BadRealloc : public Exception
	{
	public:
		BadRealloc() : Exception(ClassName) {};
		BadRealloc(std::string errContext) : Exception(ClassName, errContext) {};
		BadRealloc(std::string errContext, std::string errMsg)
			: Exception(ClassName, errContext, errMsg) {}
		BadRealloc(std::string errContext, std::string errMsg, Exception* nestedException)
			: Exception(ClassName, errContext, errMsg, nestedException) {}
	};

	enum class BufferSeek
	{
		Start, Relative, End
	};
}
