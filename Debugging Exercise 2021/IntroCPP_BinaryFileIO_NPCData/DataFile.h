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

	//void AddRecord(const char* imageFilename, const char* name, int age);
	Record* GetRecord(const char* filename, int index);

	int GetRecordCount() { return recordCount; };

	//void Save(const char* filename);
	//void Load(const char* filename);

private:
	//void Clear();

	int recordCount;
	Record* currentRecord;
	/*std::vector<Record*> records;*/	// delete this vector. Load only the required record 
};

