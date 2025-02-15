#include "../include/SceneOne.hpp"
#include "../include/SceneTwo.hpp"
#include "../include/Game.hpp"
#include "../include/WalkingEnemy.hpp"

SceneOne::SceneOne(Game* game) 
    : Scene(game), game(game), 
    shooterEnemy1(Vector2{1350, 300}),
    shooterEnemy2(Vector2{1350, 150}),
    shooterEnemy3(Vector2{1350, 525})
{
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
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, door)) {
        game->character->transitioning = true;
    }
    game->character->move(platforms, platformCount);
    walkingEnemy.move();
    shooterEnemy1.move();
    shooterEnemy2.move();
    shooterEnemy3.move();
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, walkingEnemy.getPosition())) {
        game->character->dead = true;
    }
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, shooterEnemy1.getPosition())) {
        game->character->dead = true;
    }
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, shooterEnemy2.getPosition())) {
        game->character->dead = true;
    }
    if (game->AtOject({game->character->position.x, game->character->position.y, game->character->characterWidth, game->character->characterHeight}, shooterEnemy3.getPosition())) {
        game->character->dead = true;
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

    // Draw game->character
    Rectangle source = { game->character->frameWidth * game->character->currentFrame, 0, game->character->frameWidth, game->character->frameHeight };
    Rectangle dest = { game->character->position.x, game->character->position.y, game->character->frameWidth * game->character->spriteScale, game->character->frameHeight * game->character->spriteScale };
    DrawTexturePro(game->character->spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);

    // Draw Enemies
    DrawRectangleRec(door, RED);
    DrawRectangleRec(walkingEnemy.position, MAROON);
    DrawRectangleRec(shooterEnemy1.getPosition(), GREEN);
    DrawRectangleRec(shooterEnemy2.getPosition(), GREEN);
    DrawRectangleRec(shooterEnemy3.getPosition(), GREEN);
    
    // Draw Texts
    DrawText("Use arrow keys to move!", 10, 10, 30, DARKPURPLE);
    DrawText("Press SPACE to Jump!", 10, 40, 30, DARKPURPLE);

    // Draw fade effect
    if (game->character->alpha > 0.0f || game->character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, Fade(BLACK, game->character->alpha));
    }
    if (game->character->alpha2 > 0.0f) {
        DrawRectangle(0, 0, 1400, 700, Fade(BLACK, game->character->alpha2));
    }
}
