/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Ethan's Visual Novel Interpreter");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    Image background = LoadImage("assets/highway.png");
    Image carSprite = LoadImage("assets/CarSprite02.png");
    
    Texture2D img_tex = LoadTextureFromImage(background);
    Texture2D car_sprite = LoadTextureFromImage(carSprite);
    
    
    // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    Font fontTtf = LoadFontEx("assets/tahoma.ttf", 28, 0, 250);
    const char msg[] = "Dialogue/narration goes here.";
    const char msg2[] = "This is the second line of dialogue.";
    
    float scrollingForeX = 0.0f;
    float scrollingForeY = -880.0f;
    //int scrollIter = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        
      
        
        if (scrollingForeX <= -(img_tex.width / 2)) 
        {
            scrollingForeX = 0.0f;
            scrollingForeY = -880.0f;
        }
        BeginDrawing();

        //ClearBackground(RAYWHITE);
        ClearBackground(GetColor(0x052c46ff));
        
        //void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint); 
        
        //DrawTextureRec(img_tex, (Rectangle) { 0, 880, 799, 1480 }, (Vector2) { 0.0f, 0.0f }, WHITE); 
        //DrawTexture(img_tex, 0,0, WHITE);
        
        DrawTextureEx(img_tex, (Vector2){ scrollingForeX, scrollingForeY }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(img_tex, (Vector2){ scrollingForeX, scrollingForeY }, 0.0f, 1.0f, WHITE);
        DrawTexture(car_sprite, 220, 230, WHITE);
        
        //DrawTextEx(fontTtf, msg, (Vector2){ 63.0f, 629.0f }, (float)fontTtf.baseSize, 2, DARKGRAY);
        //DrawTextEx(fontTtf, msg2, (Vector2){ 63.0f, 653.0f }, (float)fontTtf.baseSize, 2, DARKGRAY);
        //DrawTexture(texture, 0, 0, CLITERAL(Color){ 255, 255, 255, 128 });
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        
        // Scrolling formula:  X = 2, Y = 1.155
        scrollingForeX -= 8.0f;
        
     
        scrollingForeY -=4.62;
        
        //scrollIter++;
        EndDrawing();
        //while(!IsKeyDown(KEY_SPACE))
        //{;;}
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

 