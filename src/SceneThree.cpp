#include "../include/SceneTwo.hpp"
#include "../include/SceneOne.hpp"
#include "../include/SceneThree.hpp"
#include "raylib.h"

SceneThree::SceneThree(Game* game) 
    : Scene(game), game(game), 
    character(game), 
    seekingEnemy1(Vector2{50, 100}),
    seekingEnemy2(Vector2{1300, 100})
{
    // Load backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");

    // Create door
    door = { 130, 500, 50, 75 };

    // Initialize the platforms
    platforms[0] = { 400, 550, 500, 20 };
}

SceneThree::~SceneThree() {
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
}

void SceneThree::update() {
    if (game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, door)) {
        game->setScene(new SceneOne(game));
    }
    character.move(platforms, platformCount);
    seekingEnemy1.move(character.getPosition());
    seekingEnemy2.move(character.getPosition());
    if (game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, seekingEnemy1.getPosition())) {
        character.dead = true;
    }
    if(game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, seekingEnemy2.getPosition())) {
        character.dead = true;
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

    // Draw character
    Rectangle source = { character.frameWidth * character.currentFrame, 0, character.frameWidth, character.frameHeight };
    Rectangle dest = { character.position.x, character.position.y, character.frameWidth * character.sprite_Scale, character.frameHeight * character.sprite_Scale };
    DrawTexturePro(character.spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);
    
    // Draw rectangles
    DrawRectangleRec(door, RED);
    DrawRectangleRec(seekingEnemy1.getPosition(), MAROON);
    DrawRectangleRec(seekingEnemy2.getPosition(), MAROON);

    // Draw Texts
    DrawText("Good luck!", 10, 10, 20, PURPLE);

    // Draw fade effect
    if (character.alpha > 0.0f || character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, character.alpha));
    }
    if (character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, character.alpha2));
    }
}