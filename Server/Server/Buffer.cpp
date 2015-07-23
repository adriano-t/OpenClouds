

#include "Buffer.h"
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
		return index;
	}


	void Buffer::WriteInt32(const int32_t value)
	{
		int diff = size - (index + 1);

		if (diff >= sizeof(int32_t))
		{
			data[index++] = value;
			data[index++] = (value >> 1);
			data[index++] = (value >> 2);
			data[index++] = (value >> 3);
		}
		else
		{
			//resize the data buffer
			size += blockSize;
			if ((data = (int8_t*)realloc(data, size)) == nullptr)
			{
				// throw(new MemoryException("error: impossible to allocate the buffer"));
			}
		}
	}
 
	void Buffer::Reserve(const int size)
	{
		// resize the data buffer realloc() 
		this->size = size;
		if ((data = (int8_t*)realloc(data, size)) == nullptr)
		{
			// throw(new MemoryException("error: impossible to allocate the buffer"));
		}
	}

}