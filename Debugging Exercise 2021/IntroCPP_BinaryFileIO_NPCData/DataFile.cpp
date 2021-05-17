#include "DataFile.h"
#include <fstream>
using namespace std;

//Initialize the values from the header file
DataFile::DataFile()
{
	recordCount = 0;
	currentRecord = new Record();
}

//Destructor
DataFile::~DataFile()
{
}

//Load/Read the file of the profile
Record* DataFile::GetRecord(int index, const char* filename)
{
	//Open up the file
	ifstream infile(filename, ios::binary);

	//Initialize the value to zero to start the loop back to the start
	recordCount = 0;

	//Looks for a single profile to load than all by setting the recordCount value to the int size of currentRecordIdx
	infile.read((char*)&recordCount, sizeof(int));

	//Loops through the process of reading the profile to the program
	for (int i = 0; i < recordCount; i++)
	{		
		//Size
		//Declares the size of the data that will be read
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;
		
		//Reads into the file and change the width and height vaule by the size of the int
		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));
		
		//Multiple the vaules of width, height, and the sizeof Colour into the imageSize value
		imageSize = sizeof(Color) * width * height;
		
		//Gets the name and age and set there vaule to there int size from there profile being read
		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));
		
		//Adds all the final values into on new variable
		int recordSize = imageSize + nameSize + ageSize;

		//If i value equals the profile number run
		if (i == index)
		{
			//runs always and to delete new variables Declared
			if (currentRecord)
			{
				UnloadImage(currentRecord->image);
				delete[] currentRecord->name;
				delete currentRecord;
			}
			//Data
			//Copys the value of int imageSize by cast to a char pointer imgdata value
			char* imgdata = new char[imageSize];
			infile.read(imgdata, imageSize);

			//Declares a new variable inside this scope as it was private
			currentRecord = new Record();

			//Image equals all the code on the right side as a pointer that can be called from a different file
			currentRecord->image = LoadImageEx((Color*)imgdata, width, height);

			//Moves the value from nameSize over to name with the maximum characters space
			//Add 1 to the nameSize so it will stop reading at 0 than keep reading random bytes
			currentRecord->name = new char[nameSize + 1];

			//Reads the name and age into the file
			infile.read(currentRecord->name, nameSize);
			infile.read((char*)&currentRecord->age, ageSize);
			currentRecord->name[nameSize] = 0;

			//Deletes the imgdata
			delete[] imgdata;

			//Breaks from the for loop
			break;
		}
		else
		{
			//If i != index than read there RecordSize
			infile.seekg(recordSize, std::ios::cur);
		}	
	}
	//Close file
	infile.close();

	//Return currentRecord value
	return currentRecord;
}