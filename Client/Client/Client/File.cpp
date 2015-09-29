#include "File.h"

unsigned char FileReader::operator[](uint64_t pos)
{
	static const int32_t buffSize = 1000000;
	static uint8_t  buffer[buffSize]; // 1 MB buffer
	static uint64_t start_addr = 0;
	static uint64_t bytes_read = 0;

	if (src == NULL) // Not initialized
		return(0);
	
	// If pos belongs to preloaded data, retrieve it
	if (pos >= start_addr && pos < start_addr + bytes_read)
		return(buffer[pos - start_addr]);

	// otherwise, reload
	fseek(src, pos, SEEK_SET);
	bytes_read = (uint64_t) fread(buffer, 1, buffSize, src);
}


FileReader::FileReader(const std::string& fname)
{
	FileReader(fname.c_str());
}
FileReader::FileReader(const char* fname)
{
	if ((src = fopen(fname, "rb")) == NULL)
	{
		return;
	}
	fseek(src, 0, SEEK_END);
	fpos_t a;
	fgetpos(src, &a);
	len = a;
}