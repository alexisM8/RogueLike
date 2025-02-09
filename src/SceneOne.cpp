#include "../include/SceneOne.hpp"
#include "../include/SceneTwo.hpp"
#include "../include/Game.hpp"
#include "../include/WalkingEnemy.hpp"

SceneOne::SceneOne(Game* game) : Scene(game) {
    // Load backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");
    
    // Create door
    door = { 1325, 75, 50, 75 };

    // Initialize the platforms
    platforms[0] = { 50, 600, 150, 20 };
    platforms[1] = { 400, 500, 125, 20 };
    platforms[2] = { 750, 375, 100, 20 };
    platforms[3] = { 1050, 250, 100, 20 };
    platforms[4] = { 1300, 150, 100, 20 };
}
SceneOne::~SceneOne() {
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
}

void SceneOne::update() {
    if (game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, door)) {
        game->setScene(new SceneTwo(game));  // Transition to SceneTwo
    }
    walkingEnemy.move();
    character.move(platforms, platformCount);
    if (game->AtOject({character.position.x, character.position.y, character.characterWidth, character.characterHeight}, walkingEnemy.getPosition())) {
        character.dead = true;
    }
    
}

void SceneOne::render() {
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

    // Draw Enemies
    DrawRectangleRec(door, RED);
    DrawRectangleRec(walkingEnemy.position, MAROON);
    
    // Draw Texts
    DrawText("Use arrow keys to move!", 10, 10, 20, DARKGRAY);
    DrawText("Press SPACE to Jump!", 10, 30, 20, DARKGRAY);

    // Draw fade effect
    if (character.alpha > 0.0f || character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, character.alpha));
    }
    if (character.alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, character.alpha2));
    }
}
