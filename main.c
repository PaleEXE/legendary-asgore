#include "raylib.h"

int main(void)
{
    Texture2D sprite;
    Sound sound;
    Music music;
    
    InitWindow(800, 450, "asgore window");
    
    InitAudioDevice();
    
    sprite = LoadTexture("asgore.jpeg");
    sound = LoadSound("car-engine-roaring-376881.mp3");
    music = LoadMusicStream("Asgore-Runs-Over-Dess.wav");
    PlayMusicStream(music);
    
    float posX = -sprite.width;
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        
        posX += GetFrameTime() * 300;
        if (posX > 800)
        {
            posX = -sprite.width;
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Rectangle spriteRect = {
                posX,
                10,
                sprite.width,
                sprite.height
            };
            
            if (CheckCollisionPointRec(GetMousePosition(), spriteRect))
            {
                PlaySound(sound);
            }
        }
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            DrawTexture(sprite, posX, 10, WHITE);
            
        EndDrawing();
    }
    
    StopMusicStream(music);
    
    CloseAudioDevice();
    
    CloseWindow();
    
    return 0;
}