#include "DataFile.h"
#include <fstream>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
	currentRecord = new Record();
}

DataFile::~DataFile()
{
}


Record* DataFile::GetRecord(int index, const char* filename)
{
	ifstream infile(filename, ios::binary);
	
	recordCount = 0;
	infile.read((char*)&recordCount, sizeof(int));
	
	for (int i = 0; i < recordCount; i++)
	{		
		//Size
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;
	
		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));
	
		imageSize = sizeof(Color) * width * height;
	
		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));
		
		int recordSize = imageSize + nameSize + ageSize;

		if (i == index)
		{
			if (currentRecord)
			{
				UnloadImage(currentRecord->image);
				delete[] currentRecord->name;
				delete currentRecord;
			}
			//Data
			char* imgdata = new char[imageSize];
			infile.read(imgdata, imageSize);
	
			currentRecord = new Record();
			currentRecord->image = LoadImageEx((Color*)imgdata, width, height);
			currentRecord->name = new char[nameSize+1];
			infile.read(currentRecord->name, nameSize);
			infile.read((char*)&currentRecord->age, ageSize);
			currentRecord->name[nameSize] = 0;

			delete[] imgdata;
			break;
		}
		else
		{
			infile.seekg(recordSize, std::ios::cur);
		}	
	}
	infile.close();

	return currentRecord;
}
