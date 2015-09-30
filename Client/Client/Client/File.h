#ifndef FILE_H
#define FILE_H
#define BUFFSIZE 1000000
class FileReader
{
private:
	FILE* src;
	uint64_t len;
	const int32_t buffSize = BUFFSIZE;
	uint8_t  buffer[BUFFSIZE];
	uint64_t start_pos = 0;
	uint64_t end_pos = 0;
public:
	FileReader() { src = NULL; }
	FileReader(const std::string& name);
	FileReader(const char* name);
	uint8_t  operator[](uint64_t i);
	uint64_t length() { return len; }
};

void GetFDiff(FileReader& fileNew, FileReader& fileOld);
#endif // FILE_H