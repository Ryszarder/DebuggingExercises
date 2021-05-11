#pragma once
#include "raylib.h"
#include <vector>

using namespace std;

//Delares the Record variable type
struct Record 
{
	Image image;
	char* name;
	int age;
};

//Declares the functions that are public and private
class DataFile
{
public:
	//Creates the constructor and destructor
	DataFile();
	~DataFile();

	//Load and get the profile from the file that has been ask for
	Record* GetRecord(int index, const char* filename);

	//Get the position number of the profile 
	int GetRecordCount() { return recordCount; };

private:
	//variable is used to hold the position number of the proflie
	int recordCount;

	//Declares a pointer from Record to currentRecord
	Record* currentRecord;
};

