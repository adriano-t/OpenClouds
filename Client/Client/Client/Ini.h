#ifndef INI_H
#define INI_H
#include "Includes.h"
class Ini
{
private:
	struct Value
	{
		std::string name;
		std::string value;
	};
	Value** values;
	int valueCount;
	void clearValues();
public:
	Ini();
	Ini(const std::string& fname);
	~Ini();
	void readFile(const std::string& fname);
	int  getValueCount() { return valueCount; }
	Value*  getValue(int n) { return((n < 0 || n >= valueCount) ? nullptr : values[n]); }
};
#endif // INI_H