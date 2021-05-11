#include "raylib.h"
#include "DataFile.h"

//Where the program starts when launch
int main()
{
	//--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
	//Set the window pop-up width, height, the title of the window, and the frames pre second
    InitWindow(800, 450, "Debug Exercise");
	SetTargetFPS(60);

	//Load the data file
    DataFile data;

	//Set the vaule to 0 to load the first profile when launch
    int currentRecordIdx = 0;

	//Runs to get the data of the profile by the function by giving it the currentRecord value and the file name to read from
    Record* currentRecord = data.GetRecord(currentRecordIdx, "npc_data.dat");

	//Get the image allocated to the profile
    Texture2D recordTexture = LoadTextureFromImage(currentRecord->image);
    
	//While loop when program is running and stop when not
    while (!WindowShouldClose())
    {
		//--------------------------------------------------------------------------------------
		// Update
		//--------------------------------------------------------------------------------------
		//When left arrow key is press run if statement
        if (IsKeyPressed(KEY_LEFT))
        {
			//minus 1 from currentRecordIdx value
            currentRecordIdx--;
			
			//If value of currentRecordIdx is smaller than 0 run
            if (currentRecordIdx < 0)
            {
				//Set currentRecordIdx value to 0 as they can't go backwards
                currentRecordIdx = 0;
            }
			//Get data of the new profile and image
            currentRecord = data.GetRecord(currentRecordIdx, "npc_data.dat");
            recordTexture = LoadTextureFromImage(currentRecord->image);
        }

		//When left arrow key is press run if statement
        if (IsKeyPressed(KEY_RIGHT))
        {
			//Plus 1 to currentRecordIdx value
            currentRecordIdx++;
			
			//If currentRecordIdx value greater or equal to GetRecordCount run
            if (currentRecordIdx >= data.GetRecordCount())
            {
				//Set currentRecordIdx to data.GetRecordCount - 1 
                currentRecordIdx = data.GetRecordCount()-1;
            }
			//Get data of the new profile and image
            currentRecord = data.GetRecord(currentRecordIdx, "npc_data.dat");
            recordTexture = LoadTextureFromImage(currentRecord->image);
        }


		//--------------------------------------------------------------------------------------
        // Draw
		//--------------------------------------------------------------------------------------
		//Start Drawing
        BeginDrawing();

		//Set background colour to white
        ClearBackground(RAYWHITE);

		//Draw the profile image
        DrawTexture(recordTexture, 300, 50, WHITE);

		//Draw the string "NAME" as grey colour and currentRecord->name as grey colour
        DrawText("NAME", 10, 50, 20, LIGHTGRAY);
        DrawText(currentRecord->name, 10, 80, 20, LIGHTGRAY);

		//Draw the string "AGE" as grey colour
        DrawText("AGE", 10, 120, 20, LIGHTGRAY);

		//Draw the currentRecord->age as grey colour
		char text[16];
		sprintf_s(text, 16, "%i", currentRecord->age);
        DrawText(text, 10, 150, 20, LIGHTGRAY);

		//End drawing
        EndDrawing();
    }

	//--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();

    return 0;
}