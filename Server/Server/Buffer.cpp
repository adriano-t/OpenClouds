#include "Buffer.h"

#include <iostream>
#include <string>
#include "Utils.h"
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
			index = size + offset;
			break;
		}

		if (index < 0 || index >= size)
			throw(new IndexOutOfBound());
	}

	void Buffer::Seek(const int position)
	{
		Seek(BufferSeek::Relative, position);
	}

	void Buffer::Clear()
	{
		//memfree(data)
		index = 0;
		delete[] data;
		data = nullptr;
		size = 0;
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
		data = (int8_t*)std::realloc(data, size + amount);
		if (data == nullptr)
			throw(new BadRealloc(GetContext()));
		size += amount;
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
			throw(new IndexOutOfBound());
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
			throw( new IndexOutOfBound() );
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
			throw(new IndexOutOfBound());
		}
	}
	 
	void Buffer::Reserve(const int size)
	{
		// resize the data buffer realloc() 
		this->size = size;
		data = (int8_t*)std::realloc(data, size);
		if (data == nullptr)
		{
			throw(new BadRealloc());
		}
	}


	int8_t Buffer::GetByte(int i) const
	{
		if (i >= 0 && i < size)
			return data[i];
		else
		{
			throw(new IndexOutOfBound());
		}
	}

	int8_t Buffer::operator[](int i) const
	{
		if (i > 0 && i < size)
			return data[i];
		else{
			throw(new IndexOutOfBound());
			return 0;
		}
	} 

	void Buffer::WriteString(const std::string& str)
	{ 

		int diff = (index + str.length() * sizeof(char) + 1) - size;
		if (diff >= 0)
		{
			IncreaseSize(diff);
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