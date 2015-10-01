#include "includes.h"
unsigned char FileReader::operator[](uint64_t pos)
{
	start_pos = 0;
	end_pos = 0;

	if (src == NULL) // Not initialized
		return(0);
	
	// If pos belongs to preloaded data, retrieve it
	if (pos >= start_pos && pos < end_pos)
		return(buffer[pos - start_pos]);

	// otherwise, reload
	fseek(src, pos, SEEK_SET);
	end_pos = (uint64_t)fread(buffer, 1, buffSize, src) + start_pos;
	start_pos = pos;
	return(buffer[0]);
}


FileReader::FileReader(const std::string& fname)
{
	FileReader(fname.c_str());
}
FileReader::FileReader(const char* fname)
{
	fopen_s(&src, fname, "rb");
	if (src == NULL)
		return;
	fseek(src, 0, SEEK_END);
	fpos_t a;
	fgetpos(src, &a);
	len = a;
}
