

#include "Buffer.h"

//test
#include <iostream>

#include <string>

using namespace std;

namespace OpenClouds
{

	Buffer::Buffer()
	{
		blockSize = 32;
		data = new int8_t[blockSize];
		size = blockSize;
	}

	Buffer::Buffer(const int startSize, const int blockSize)
		: size(startSize), blockSize(blockSize)
	{
		data = new int8_t[startSize];
	}

	void Buffer::Seek(BufferSeek seek, const int offset)
	{
		switch (seek)
		{
		case BufferSeek::Start:
			index = offset;
			break;
		case BufferSeek::Relative:
			index += offset;
			break;
		case BufferSeek::End:
			index = size + offset; //WARNING: OUT OF BOUND
			break;
		}
	}

	void Buffer::Seek(const int position)
	{
		index = position;
	}

	void Buffer::Clear()
	{
		//memfree(data)
		index = 0;
	}

	int Buffer::GetIndex() const
	{
		return index;
	}

	int Buffer::GetSize() const
	{
		return size;
	}

	void Buffer::IncreaseSize(const int amount)
	{
		size += amount;
		if ((data = (int8_t*)realloc(data, size)) == nullptr)
		{
			// throw(new MemoryException("error: impossible to allocate the buffer"));
		}

	}

	void Buffer::WriteInt32(const int32_t value)
	{
		if (index + 4 > size)
		{
			IncreaseSize(blockSize);
		}
		data[index++] = (value >> 24);
		data[index++] = (value >> 16);
		data[index++] = (value >> 8);
		data[index++] = value;
	}

	int32_t Buffer::ReadInt32()
	{ 
		if (index + 4 <= size)
		{
			int32_t value = 0;
			value |= data[index++] & 0xff; 
			value <<= 8;
			value |= data[index++] & 0xff;
			value <<= 8;
			value |= data[index++] & 0xff;
			value <<= 8;
			value |= data[index++] & 0xff;
			return value;
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}
	}

	void Buffer::WriteUint32(const uint32_t value)
	{

		if (index + 4 > size)
		{
			IncreaseSize(blockSize);
		}

		data[index++] = (value >> 24);
		data[index++] = (value >> 16);
		data[index++] = (value >> 8);
		data[index++] = value;
	}

	uint32_t Buffer::ReadUint32()
	{
		if (index + 4 <= size)
		{

			int32_t value = 0;
			value |= data[index++];
			value <<= 8;
			value |= data[index++];
			value <<= 8;
			value |= data[index++];
			value <<= 8;
			value |= data[index++];

			return value;
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}
	}


	void Buffer::WriteInt16(const int16_t value)
	{ 

		if (index + 2 > size)
		{
			IncreaseSize(blockSize);
		}
		data[index++] = (value >> 8);
		data[index++] = (int8_t)value;
	}

	int16_t Buffer::ReadInt16()
	{
		if (index + 2 <= size)
		{
			int16_t value = 0;

			value |= data[index++] & 0xff;
			value <<= 8;
			value |= data[index++] & 0xff;

			return value;
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}

	}

	void Buffer::WriteUint16(const uint16_t value)
	{

		if (index + 2 > size)
		{
			IncreaseSize(blockSize);
		}
		data[index++] = (value >> 8);
		data[index++] = (int8_t)value;
	}



	uint16_t Buffer::ReadUint16()
	{
		if (index + 2 <= size)
		{
			int16_t value = 0;

			value |= data[index++];
			value <<= 8;
			value |= data[index++];

			return value;
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}

	}


	void Buffer::WriteInt8(const int8_t value)
	{
		if (index + 1 > size)
		{
			IncreaseSize(blockSize);
		}
		data[index++] = value;
	}

	int8_t Buffer::ReadInt8()
	{
		if (index + 1 <= size)
		{
			return data[index++];
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}
	}

	void Buffer::WriteUint8(const uint8_t value)
	{
		if (index + 1 > size)
		{
			IncreaseSize(blockSize);
		}
		data[index++] = value;
	}

	uint8_t Buffer::ReadUint8()
	{
		if (index + 1 <= size)
		{
			return data[index++];
		}
		else
		{
			//throw(new BufferReadException("error: int32_t buffer size less than 4 bytes"));
			return 0;
		}
	}
 
	void Buffer::Reserve(const int size)
	{
		// resize the data buffer realloc() 
		this->size = size;
		if ((data = (int8_t*)realloc(data, size)) == nullptr)
		{
			//throw(new MemoryException("error: impossible to allocate the buffer"));
		}
	}


	int8_t Buffer::GetByte(int i) const
	{
		if (i >= 0 && i < size)
			return data[i];
		else{
			//throw(new MemoryException("error: impossible to allocate the buffer"));
			return 0;
		}
	}

	//Does not work
	int8_t Buffer::operator [](int i) const
	{
		if (i > 0 && i < size)
			return data[i];
		else{
			//throw(new MemoryException("error: impossible to allocate the buffer"));
			return 0;
		}
	}

	void Buffer::WriteString(const std::string& str)
	{
		int diff = (index + str.length() * sizeof(char) + 1) - size;
		if (diff >= 0)
		{
			IncreaseSize(diff + blockSize);
		}

		for (char c : str)
		{
			data[index++] = c;
		}
	}

	std::string Buffer::ReadString()
	{
		return "not implemented";
	}

}