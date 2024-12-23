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
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Ethan's Visual Novel Interpreter");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    Image background = LoadImage("assets/photobackground01.png");
    Image textbackdrop = LoadImage("assets/textbackdrop.png");
    Image buttonsbackdrop = LoadImage("assets/buttonsbackdrop.png");
    Image loadbutton = LoadImage("assets/loadbutton.png");
    Image logbutton = LoadImage("assets/logbutton.png");
    Image repeatbutton = LoadImage("assets/repeatbutton.png");
    Image skipbutton = LoadImage("assets/skipbutton.png");
    Image savebutton = LoadImage("assets/savebutton.png");
    
    Texture2D img_tex = LoadTextureFromImage(background);
    Texture2D text_backdrop = LoadTextureFromImage(textbackdrop);
    Texture2D buttons_backdrop = LoadTextureFromImage(buttonsbackdrop);
    Texture2D load_button = LoadTextureFromImage(loadbutton);
    Texture2D log_button = LoadTextureFromImage(logbutton);
    Texture2D skip_button = LoadTextureFromImage(skipbutton);
    Texture2D save_button = LoadTextureFromImage(savebutton);
    Texture2D repeat_button = LoadTextureFromImage(repeatbutton);
    
    // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    Font fontTtf = LoadFontEx("assets/tahoma.ttf", 28, 0, 250);
    const char msg[] = "Dialogue/narration goes here.";
    const char msg2[] = "This is the second line of dialogue.";
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
       
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        DrawTexture(img_tex, 0,0, WHITE);
        DrawTexture(text_backdrop, 31, 607, CLITERAL(Color){ 255, 255, 255, 192 } );
        DrawTexture(buttons_backdrop, 1055, 479, WHITE);
        DrawTexture(save_button, 1055, 511, WHITE);
        DrawTexture(load_button, 1055, 543, WHITE);
        DrawTexture(skip_button, 1055, 575, WHITE);
        DrawTexture(log_button, 1055, 607, WHITE);
        DrawTexture(repeat_button, 1055, 639, WHITE);
        
        DrawTextEx(fontTtf, msg, (Vector2){ 63.0f, 629.0f }, (float)fontTtf.baseSize, 2, DARKGRAY);
        DrawTextEx(fontTtf, msg2, (Vector2){ 63.0f, 653.0f }, (float)fontTtf.baseSize, 2, DARKGRAY);
        //DrawTexture(texture, 0, 0, CLITERAL(Color){ 255, 255, 255, 128 });
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

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
