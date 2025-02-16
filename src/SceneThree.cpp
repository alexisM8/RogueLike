#include "../include/SceneTwo.hpp"
#include "../include/SceneOne.hpp"
#include "../include/SceneThree.hpp"
#include "raylib.h"

SceneThree::SceneThree(Game* game) 
    : Scene(game), game(game), 
    seekingEnemy1(Vector2{50, 100}),
    seekingEnemy2(Vector2{1300, 100})
{
    // Load backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");

    // Create door
    door = { 1300, 350, 50, 75 };

    // Initialize the platforms
    platforms[0] = { 400, 575, 500, 20 };
    platforms[1] = { 600, 420, 150, 20 };
    platforms[2] = { 1300, 425, 50, 20 };
}

SceneThree::~SceneThree() {
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
}

void SceneThree::update() {
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, door)) {
        game->wonGame = true;
    }
    game->character->move(platforms, platformCount);
    seekingEnemy1.move(game->character->getPosition());
    seekingEnemy2.move(game->character->getPosition());
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, seekingEnemy1.getPosition())) {
        game->character->dead = true;
    }
    if(game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, seekingEnemy2.getPosition())) {
        game->character->dead = true;
    }
}

void SceneThree::render() {
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

    // Draw game->character->   
    Rectangle source = { game->character->frameWidth * game->character->currentFrame, 0, game->character->frameWidth, game->character->frameHeight };
    Rectangle dest = { game->character->position.x, game->character->position.y, game->character->frameWidth * game->character->spriteScale, game->character->frameHeight * game->character->spriteScale };
    DrawTexturePro(game->character->spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);
    
    // Draw rectangles
    DrawRectangleRec(door, RED);
    DrawRectangleRec(seekingEnemy1.getPosition(), MAROON);
    DrawRectangleRec(seekingEnemy2.getPosition(), MAROON);

    // Draw Texts
    DrawText("Good luck!", 10, 10, 30, DARKPURPLE);

    // Draw fade effect
    if (game->character->alpha > 0.0f || game->character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, game->character->alpha));
    }
    if (game->character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, game->character->alpha2));
    }
}