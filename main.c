#include "include/raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define SPEED 400

int main(void)
{
    Texture2D sprite;
    Sound sound;
    Music music;

    InitWindow(WIDTH, HEIGHT, "asgore window");
    
    InitAudioDevice();
    
    sprite = LoadTexture("assets/img/asgore.jpeg");
    sound = LoadSound("assets/sound/car-engine-roaring-376881.mp3");
    music = LoadMusicStream("assets/sound/Asgore-Runs-Over-Dess.wav");
    PlayMusicStream(music);
    
    float posX = WIDTH / 2.0f - sprite.width / 2.0f;
    float posY = HEIGHT / 2.0f - sprite.height / 2.0f;
    float dx = 1, dy = 1;
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        
        posX += GetFrameTime() * SPEED * dx;
        posY += GetFrameTime() * SPEED * dy;
        if (posX + sprite.width > WIDTH)   dx = -1;
        if (posY + sprite.height > HEIGHT) dy = -1;
        if (posX < 0.0f) dx = 1;
        if (posY < 0.0f) dy = 1;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Rectangle spriteRect = {
                posX,
                posY,
                sprite.width,
                sprite.height
            };
            
            if (CheckCollisionPointRec(GetMousePosition(), spriteRect))
            {
                PlaySound(sound);
                dx *= -1.1;
                dy *= -1.1;
            }
        }
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            DrawTexture(sprite, posX, posY, WHITE);
            
        EndDrawing();
    }
    
    StopMusicStream(music);
    
    CloseAudioDevice();
    
    CloseWindow();
    
    return 0;
}