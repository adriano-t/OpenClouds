#ifndef FILE_H
#define FILE_H
#include "Includes.h"
class FileReader
{
private:
	FILE* src;
	uint64_t len;
public:
	FileReader() { src = NULL; }
	FileReader(const std::string& name);
	FileReader(const char* name);
	uint8_t  operator[](uint64_t i);
	uint64_t length() { return len; }
};

#endif // FILE_H