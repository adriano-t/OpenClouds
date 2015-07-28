#pragma once

#include <string>
#include "Log.h"

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
			className = "OpenClouds::Exception";
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
			std::string header = "   ";
			std::string className;

			while (ptr != nullptr)
			{

				if (ptr->errContext.length() > 0)
					Log::Writeln(header + ptr->className + " occurred in [" + 
					ptr->errContext + "]: ", true);
				else
					Log::Writeln(header + ptr->className + " occurred in [unknown context]: ",
					true);

				if (ptr->errMessage.length() > 0)
					Log::Writeln(header + ptr->errMessage, true);
				else
					Log::Writeln(header + "no error message.", true);

				ptr = ptr->nestedException;
				header += "   ";
			}
		}
	};

	class IndexOutOfBound : Exception
	{
	public:
		IndexOutOfBound() : Exception() { className = typeid(*this).name(); };
	};

	class BadRealloc : Exception
	{
	public:
		BadRealloc() : Exception() {};
		BadRealloc(std::string errContext) : Exception(errContext) {};
		BadRealloc(std::string errContext, std::string errMsg) : Exception(errContext, errMsg) {};
		BadRealloc(std::string errContext, std::string errMsg, Exception* nestedException) 
			: Exception(errContext, errMsg, nestedException) {
			className = "BadRealloc";
		};
		void pst() {
			className = typeid(*this).name();
			PrintStackTrace();
		}
	};
	enum class BufferSeek{
		Start, Relative, End
	};
}
