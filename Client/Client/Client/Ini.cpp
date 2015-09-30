#include "includes.h"
Ini::Ini(const std::string& fname)
{
	values = nullptr;
	readFile(fname);
}

Ini::Ini()
{
	values = nullptr;
}
void Ini::readFile(const std::string& fname)
{
	std::ifstream file(fname);
	std::string line;
	int lineCount = 0;

	// Count number of valid values
	while (std::getline(file, line))
	{
		size_t equalPos = line.find("=");


		// Discard invalid lines
		if (equalPos == std::string::npos)
			continue;
		if (equalPos == line.length() - 1)
			continue;
		// TODO: check if name is empty (only white spaces)


		// Line was valid, increase conter
		lineCount++;
	}

	if (lineCount == 0)
	{
		file.close();
		return;
	}

	clearValues();
	// Reset file to beginning and perform the actual reading
	file.clear();
	file.seekg(0, std::ios::beg);

	
	values = new Value*[lineCount];
	int n = 0;

	while (std::getline(file, line))
	{
		size_t equalPos = line.find("=");

		// Discard invalid lines
		if (equalPos == std::string::npos)
			continue;
		if (equalPos == line.length() - 1)
			continue;
		
		// Add valid value
		values[n] = new Value();
		values[n]->name = line.substr(0, equalPos);
		// Final white spaces in name are forbidden
		while (values[n]->name[values[n]->name.length() - 1] == ' ')
			values[n]->name.pop_back();
		// Initial white spaces in value are forbidden
		line.erase(0, equalPos + 1);
		while (line[0] == ' ')
			line.erase(0, 1);
		values[n]->value = line;
		n++;
	}

	valueCount = lineCount;
}

Ini::~Ini()
{
	clearValues();
}

void Ini::clearValues()
{
	// Cleare resources
	if (values != nullptr)
	{
		for (int i = 0; i < valueCount; i++)
			delete values[i];
		delete values;
	}
	valueCount = 0;
}