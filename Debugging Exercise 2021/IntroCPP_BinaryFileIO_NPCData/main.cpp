#include "raylib.h"
#include "DataFile.h"

int main()
{
	//--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(800, 450, "Debug Exercise");
	SetTargetFPS(60);

	//Load the data file
    DataFile data;
    int currentRecordIdx = 0;

    data.Load("npc_data.dat");

    Record* currentRecord = data.GetRecord(currentRecordIdx);
    Texture2D recordTexture = LoadTextureFromImage(currentRecord->image);
    
    while (!WindowShouldClose())
    {
		//--------------------------------------------------------------------------------------
		// Update
		//--------------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_LEFT))
        {
            currentRecordIdx--;
            if (currentRecordIdx < 0)
            {
                currentRecordIdx = 0;
            }
            currentRecord = data.GetRecord(currentRecordIdx);
            recordTexture = LoadTextureFromImage(currentRecord->image);
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            currentRecordIdx++;
            if (currentRecordIdx >= data.GetRecordCount())
            {
                currentRecordIdx = data.GetRecordCount();
            }
            currentRecord = data.GetRecord(currentRecordIdx);
            recordTexture = LoadTextureFromImage(currentRecord->image);
        }


		//--------------------------------------------------------------------------------------
        // Draw
		//--------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(recordTexture, 300, 50, WHITE);

        DrawText("NAME", 10, 50, 20, LIGHTGRAY);
        DrawText(currentRecord->name, 10, 80, 20, LIGHTGRAY);

        DrawText("AGE", 10, 120, 20, LIGHTGRAY);

		char text[16];
		sprintf_s(text, 16, "%i", currentRecord->age);
        DrawText(text, 10, 150, 20, LIGHTGRAY);

        EndDrawing();
    }

	//--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();

    return 0;
}