#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

struct Record 
{
	Image image;
	char* name;
	int age;
};

class DataFile
{
public:
	DataFile();
	~DataFile();

	Record* GetRecord(int index, const char* filename);

	int GetRecordCount() { return recordCount; };

private:
	int recordCount;
	Record* currentRecord;
};

