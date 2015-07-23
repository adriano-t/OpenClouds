

#include "Buffer.h"
namespace OpenClouds
{
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
		int diff = size - index;

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
		}
	}


}