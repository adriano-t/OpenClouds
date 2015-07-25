#pragma once
#ifndef OC_BUFFER_H
#define OC_BUFFER_H 0x414E41414E49

#include <stdint.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OpenClouds
{

	enum class BufferSeek{
		Start, Relative, End
	};

	/**
	* @brief Buffer is a class which is a buffer.
	*/
	class Buffer
	{
	private:
		int8_t* data;
		int size;
		int index;
		int blockSize;

		//internal function, used only here
		void IncreaseSize(const int amount);

	public:
		Buffer();
		Buffer(const int startSize, const int blockSize);
		~Buffer();
		Buffer(Buffer&);

		/**
		* @brief Reserve memory for the buffer
		*
		* Create memory space to avoid the resizing during the write operation
		* @param size	the number of bytes to reserve
		*/
		void Reserve(const int size);


		/**
		* @brief Insert an utf8 string into the buffer.
		*
		* The string is inserted at the position pointed by the @c index, which is then
		* automatically increased by the number of bytes inserted.
		* @param str	Reference to a std::string containing the text.
		*/
		void WriteString(const std::string& str);


		/**
		* @brief Read a utf8 string from the buffer
		*
		* The string is read from the buffer and index is increased by the string length
		* @return The current size of the buffer in bytes.
		*/
		std::string ReadString();


		/**
		* @brief Insert a 4 bytes integer into the buffer.
		*
		* The bytes are inerted at the position pointed by the @c index, which is then
		* automatically increased by the number of bytes inserted.
		* @param value	The 4 bytes integer to be inserted.
		*/
		void WriteInt32(const int32_t value);


		/**
		* @brief Insert a 2 bytes integer into the buffer.
		*
		* The bytes are inserted at the position pointed by the @c index, which is then
		* automatically increased by the number of bytes inserted.
		* @param value	The 2 bytes integer to be inserted.
		*/
		void WriteInt16(const int16_t value);


		/**
		* @brief Insert a signed byte  into the buffer.
		* 
		* The byte is inserted at the position pointed by the @c index, which is then
		* automatically increased by 1.
		* @param value	The byte to be inserted.
		*/
		void WriteInt8(const int8_t value);


		/**
		* @brief Insert generic data into the buffer.
		* 
		* Insert @p len bytes into the buffer at the position pointed by the @c
		* index. The bytes are taken from the buffer @p src. The @c index is then automatically
		* increased by the number of bytes inserted.
		* @param src	The source buffer.
		* @param len	The number of bytes to insert from @p src
		*/
		void Write(const void* src, const int len);

		/**
		* @brief Insert generic data into the buffer.
		* 
		* Insert @p len bytes into the buffer at the position pointed by the @c
		* index. The bytes are taken from the buffer @p src starting from the
		* @offset position. @c index is then automatically increased by the
		* the number of bytes inserted.
		* @param src	The source data.
		* @param len	The number of bytes to insert from @p src
		* @param offset	The position of the first byte inside @p src
		*/
		void Write(const void* src, const int len, const int offset);


		/**
		* @brief Change the position of the @c index.
		* @param seek	The start position.
		* @param offset	The offset added to the position.
		*/
		void Seek(BufferSeek seek, const int offset);
		
		/**
		* @brief Change	the position of the @c index.
		* @param position	The new position
		*/
		void Seek(const int position);
		
		/**
		* @return The current value of @c index.
		*/
		int GetIndex() const;

		/**
		* @return The current size of the buffer in bytes.
		*/
		int GetSize() const;

		
		/**
		* @brief Reads general data from the buffer.
		* 
		* Reads @p len bytes from the buffer and copies them to @p dest. @c index is the position
		* of the first byte read from the buffer. @c index is then automatically increased by the
		* number of bytes read.
		*
		* @param dest	The destination of the read data.
		* @param len	The number of bytes to read.
		*/
		void Read(const void* dest, const int len);

		/**
		* @brief Read generic data from the buffer.
		* 
		* Reads @p len bytes into @p dest.
		* @param dest	The destination of the read data.
		* @param len	The number of bytes to read.
		* @param offset	The position of the first byte written into  @p dest.
		*/
		void Read(const void* dest, const int offset, const int len);

		/**
		* @brief Read a 4 bytes integer from the buffer.
		*
		* Reads and returns a 4 bytes integer from the buffer starting at position @c index.
		* After reading, @c index is automatically increased by the number of bytes read.
		*
		* @return the integer read from the buffer.
		*/
		int32_t ReadInt32();

		
		/**
		* @brief Read a 2 bytes integer from the buffer.
		*
		* Reads and returns a 2 bytes integer from the buffer starting at position @c index.
		* After reading, @c index is automatically increased by the number of bytes read.
		*
		* @return the integer read from the buffer.
		*/
		int16_t ReadInt16();


		/**
		* @brief Read a byte integer from the buffer.
		*
		* Reads and returns a 1 byte integer from the buffer starting at position @c index.
		* After reading, @c index is automatically increased by 1.
		*
		* @return the integer read from the buffer.
		*/
		int8_t ReadInt8();

		/*
		* @brief Reads and return the byte at position @p i.
		*
		* This function does not modify @c index.
		* 
		* @param i	The position of the byte to read.
		* @return The byte at position @p i.
		*/
		int8_t operator[](int i) const;

		int8_t Buffer::GetByte(int i) const;

		/*
		* @brief utterly clears the buffer
		*/
		void Clear();

	};
}


#endif