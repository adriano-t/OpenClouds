

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
		int32_t* tempData = (int32_t*)(data + index);
		*tempData = value;
		index += 4;

	}

	int32_t Buffer::ReadInt32()
	{ 
		if (index + 4 <= size)
		{
			int32_t* tempData = (int32_t*)(data + index);
			index += 4;
			return *tempData;
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
		int16_t* tempData = (int16_t*)(data + index);
		*tempData = value;
		index += 2;

	}

	int16_t Buffer::ReadInt16()
	{
		if (index + 2 <= size)
		{
			int16_t* tempData = (int16_t*)(data + index);
			index += 2;
			return *tempData;
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

	int8_t Buffer::operator[](int i) const
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
		
		data[index++] = '\0';
	}

	std::string Buffer::ReadString()
	{ 
		const char* tempData = (char*)(data + index);
		string str = string(tempData);
		index += str.length() + 1;
		return str;
	}

}