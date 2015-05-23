#pragma once
#ifndef BUFFER_H
#define BUFFER_H 0x414E41414E49

#include <stdint.h>
#include <string>

namespace OpenClouds
{
	/**
	* @brief Buffer is a class which is a buffer.
	*/
	class Buffer
	{
	private:
		char* data;
		int size;
		int index;

	public:
		Buffer();
		~Buffer();
		Buffer(Buffer&);

		/**
		* @brief Write ansi character string to the buffer.
		* @param text	reference to a std::string containing the text.
		*/
		void WriteAnsiText(const std::string& text);
		/**
		* @brief Write 4 bytes integer to the buffer.
		* @param text	reference to a std::string containing the text.
		*/
		void WriteInt32(const int32_t value);
		/**
		* @brief Write 2 bytes integer to the buffer.
		* @param text	reference to a std::string containing the text.
		*/
		void WriteInt16(const int16_t value);
		void WriteInt8(const int8_t value);
		void Write(const void* src, const int len);
		void Write(const void* src, const int len, const int offset);

		void Seek(const int pos);
		int GetSize();

		void Read(const void* dest, const int len);
		int32_t ReadInt32();
		int16_t ReadInt16();
		int8_t ReadInt8();

		char operator [](int i);

		void Clear();

	};
}


#endif