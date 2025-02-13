#include "../include/MainScreen.hpp"
#include "../include/Game.hpp"
#include <iostream>


MainScreen::MainScreen(Game* game): game(game) {}

MainScreen::~MainScreen() {
    if (backgroundL1.id) UnloadTexture(backgroundL1);
    if (backgroundL2.id) UnloadTexture(backgroundL2);
    if (backgroundL3.id) UnloadTexture(backgroundL3);
    if (cat1.id) UnloadTexture(cat1);
    if (cat2.id) UnloadTexture(cat2);
    if (cat3.id) UnloadTexture(cat3);
    if (cat4.id) UnloadTexture(cat4);
}

void MainScreen::load() {
    // Backgrounds
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");
    
    // Cats
    cat1 = LoadTexture("../assets/Cat/IdleCatb.png");
    cat2 = LoadTexture("../assets/Cat/IdleCatt.png");
    cat3 = LoadTexture("../assets/Cat/IdleCatd.png");
    cat4 = LoadTexture("../assets/Cat/IdleCattt.png");
    spriteColumns = 7;
    spriteScale = 4.0f;
    frameWidth = cat1.width / spriteColumns;
    frameHeight = cat1.height;
    currentFrame = 0.0f;
    frameTime = 0.05f;
    timer = 0.0f;
    position = { game->screenWidth / 2.0f, game->screenHeight / 2.0f };
}

void MainScreen::update() {
    timer += GetFrameTime();
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame = (int(currentFrame) + 1) % spriteColumns;
    }


    if (IsKeyPressed(KEY_ENTER)) {
        game->firstRun = false;
    }
}

void MainScreen::render(){
    ClearBackground(RAYWHITE);

    // Create scaling for background
    float scale = 3.89;
    Rectangle source2 = {0, 0, 288, 180};
    Rectangle dest2 = {0, 0, 1400, 700};
    DrawTexturePro(backgroundL1, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(backgroundL2, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(backgroundL3, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);

    // Draw cats
    Rectangle source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
    Rectangle dest = { 100, 300, frameWidth * spriteScale, frameHeight * spriteScale };
    DrawTexturePro(cat1, source, dest, (Vector2){0, 0}, 0, WHITE);
    source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
    dest = { 200, 450, frameWidth * spriteScale, frameHeight * spriteScale };
    DrawTexturePro(cat2, source, dest, (Vector2){0, 0}, 0, WHITE);
    source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
    dest = { 1250, 500, frameWidth * spriteScale, frameHeight * spriteScale };
    DrawTexturePro(cat3, source, dest, (Vector2){0, 0}, 0, WHITE);
    source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
    dest = { 1150, 350, frameWidth * spriteScale, frameHeight * spriteScale };
    DrawTexturePro(cat4, source, dest, (Vector2){0, 0}, 0, WHITE);

    // Draw Texts
    DrawText("MEOWFICANT!", 150, 75, 150, DARKPURPLE);
    DrawText("Press enter to play!", 400, 400, 50, DARKPURPLE);
}