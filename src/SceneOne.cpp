#include "../include/SceneOne.hpp"
#include "../include/SceneTwo.hpp"
#include "../include/Game.hpp"
#include "../include/WalkingEnemy.hpp"

SceneOne::SceneOne(Game* game) 
    : Scene(game), game(game), 
    shooterEnemy1(Vector2{1350, 475})
{
    // Load backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");
    
    character = new Character(game);

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
    delete character;
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
}

void SceneOne::update() {
    if (game->AtOject({character->position.x, character->position.y, character->characterWidth, character->characterHeight}, door)) {
        character->transitioning = true;
    }
    walkingEnemy.move();
    character->move(platforms, platformCount);
    shooterEnemy1.move();
    if (game->AtOject({character->position.x, character->position.y, character->characterWidth, character->characterHeight}, walkingEnemy.getPosition())) {
        character->dead = true;
    }
    if (game->AtOject({character->position.x, character->position.y, character->characterWidth, character->characterHeight}, shooterEnemy1.getPosition())) {
        character->dead = true;
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
    Rectangle source = { character->frameWidth * character->currentFrame, 0, character->frameWidth, character->frameHeight };
    Rectangle dest = { character->position.x, character->position.y, character->frameWidth * character->spriteScale, character->frameHeight * character->spriteScale };
    DrawTexturePro(character->spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);

    // Draw Enemies
    DrawRectangleRec(door, RED);
    DrawRectangleRec(walkingEnemy.position, MAROON);
    DrawRectangleRec(shooterEnemy1.getPosition(), GREEN);
    
    // Draw Texts
    DrawText("Use arrow keys to move!", 10, 10, 20, DARKPURPLE);
    DrawText("Press SPACE to Jump!", 10, 30, 20, DARKPURPLE);

    // Draw fade effect
    if (character->alpha > 0.0f || character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, character->alpha));
    }
    if (character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, character->alpha2));
    }
}
