#include "../include/SceneTwo.hpp"
#include "../include/SceneOne.hpp"
#include "../include/SceneThree.hpp"
#include "raylib.h"

SceneTwo::SceneTwo(Game* game) : Scene(game), game(game), character(game) {
    // Load backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");
    
    // Create door
    door = { 130, 500, 50, 75 };
    
    // Initialize the platforms
    platforms[0] = { 1100, 500, 200, 20 };
    platforms[1] = { 900, 300, 50, 20 };
    platforms[2] = { 700, 300, 25, 20};
    platforms[3] = { 500, 200, 25, 20};
    platforms[4] = { 300, 500, 100, 20};
    platforms[5] = { 100, 150, 50, 20 };
}
SceneTwo::~SceneTwo() {
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
}

void SceneTwo::update() {
    if (game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, door)) {
        character.transitioning = true;
    }
    character.move(platforms, platformCount);
}

void SceneTwo::render() {
    ClearBackground(RAYWHITE);

    // Create scaling for background
    float scale = 3.89;
    Rectangle source2 = {0, 0, 288, 180};
    Rectangle dest2 = {0, 0, 1400, 700};
    DrawTexturePro(backgroundL1, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(backgroundL2, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(backgroundL3, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);

    // Draw platforms
    for (int i = 0; i < platformCount; i++) {
        DrawRectangleRec(platforms[i], DARKGRAY);
    }

    // Draw character
    Rectangle source = { character.frameWidth * character.currentFrame, 0, character.frameWidth, character.frameHeight };
    Rectangle dest = { character.position.x, character.position.y, character.frameWidth * character.sprite_Scale, character.frameHeight * character.sprite_Scale };
    DrawTexturePro(character.spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);

    // Draw rectangles
    DrawRectangleRec(door, RED);

    // Draw Texts
    DrawText("Welcome to Scene 2!", 10, 10, 20, RED);

    // Draw fade effect
    if (character.alpha > 0.0f || character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, character.alpha));
    }
    if (character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, character.alpha2));
    }
}
