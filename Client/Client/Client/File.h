#ifndef OC_FILE_H
#define OC_FILE_H
#define OC_FILE_BUFFSIZE 1000000
class FileReader
{
private:
	FILE* src;
	uint64_t len;
	const int32_t buffSize = OC_FILE_BUFFSIZE;
	uint8_t  buffer[OC_FILE_BUFFSIZE];
	uint64_t start_pos = 0;
	uint64_t end_pos = 0;
public:
	FileReader() { src = NULL; }
	FileReader(const std::string& name);
	FileReader(const char* name);
	uint8_t  operator[](uint64_t i);
	uint64_t length() { return len; }
};
struct diff
{
	enum DiffType{ Insertion, Deletion } type;
	int64_t pos, len;
};
typedef std::stack<diff*>& Diffs;
std::stack<diff*>* GetFDiff(FileReader* fileNew, FileReader* fileOld);
#endif // FILE_H