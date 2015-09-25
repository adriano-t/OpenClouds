#ifndef INI_H
#define INI_H
#include "Includes.h"
class Ini
{
private:
	struct Value
	{

	};
public:
	Ini();
	Ini(std::string& fname);
	~Ini();
	void readFile(std::string& fname);
};
#endif // INI_H