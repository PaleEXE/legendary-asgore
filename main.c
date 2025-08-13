// "The hours of folly are measured by the clock, but wisdom; no clock can measure."
// - V

#include <math.h>

#include "include/raylib.h"
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600
#define SPEED 400
#define MAX_ENTITIES 100

typedef struct Entity {
    Texture2D *sprite;
    float posX, posY, dx, dy;
} Entity;

static Entity entities[MAX_ENTITIES];
static size_t entitiesCount = 0;
static Texture2D sharedSprite;

Entity *EntityCreate(float posX, float posY) {
    if (entitiesCount >= MAX_ENTITIES) return NULL;
    Entity *entity = &entities[entitiesCount++];
    entity->sprite = &sharedSprite;
    entity->posX = posX;
    entity->posY = posY;
    entity->dx = 1;
    entity->dy = 1;
    return entity;
}

void EntityDraw(const Entity *entity) {
    DrawTexture(*entity->sprite, entity->posX, entity->posY, WHITE);
}

void EntityMove(Entity *entity, float dt) {
    entity->posX += dt * SPEED * entity->dx;
    entity->posY += dt * SPEED * entity->dy;
    if (entity->posX + entity->sprite->width >= WIDTH) entity->dx = -fabsf(entity->dx);
    if (entity->posY + entity->sprite->height >= HEIGHT) entity->dy = -fabsf(entity->dy);
    if (entity->posX <= 0.0f) entity->dx = fabsf(entity->dx);
    if (entity->posY <= 0.0f) entity->dy = fabsf(entity->dy);
}

bool GoVroomVroom(Entity *entity, Sound sound) {
    Rectangle spriteRect = { entity->posX, entity->posY, entity->sprite->width, entity->sprite->height };
    if (CheckCollisionPointRec(GetMousePosition(), spriteRect)) {
        EntityCreate(WIDTH / 2.0f, HEIGHT / 2.0f);
        PlaySound(sound);
        entity->dx *= -1.1f;
        entity->dy *= -1.1f;
        return true;
    }
    return false;
}

void EntitiesMove(float dt) {
    for (Entity *e = entities; e < entities + entitiesCount; ++e) {
        EntityMove(e, dt);
    }
}

void EntitiesDraw() {
    for (Entity *e = entities; e < entities + entitiesCount; ++e) {
        EntityDraw(e);
    }
}

void GoVroomsVrooms(Sound sound) {
    for (Entity *e = entities; e < entities + entitiesCount; ++e) {
        if (GoVroomVroom(e, sound)) return;
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "asgore window");
    InitAudioDevice();

    Sound sound = LoadSound("assets/sound/car-engine-roaring-376881.mp3");
    Music music = LoadMusicStream("assets/sound/Asgore-Runs-Over-Dess.wav");
    PlayMusicStream(music);

    sharedSprite = LoadTexture("assets/img/asgore.jpeg");
    EntityCreate(WIDTH / 2.0f, HEIGHT / 2.0f);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdateMusicStream(music);

        EntitiesMove(dt);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            GoVroomsVrooms(sound);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            EntitiesDraw();
        EndDrawing();
    }

    StopMusicStream(music);
    UnloadTexture(sharedSprite);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
