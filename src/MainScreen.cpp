#include "../include/MainScreen.hpp"
#include "../include/Game.hpp"
#include <iostream>


MainScreen::MainScreen(Game* game): game(game) {}

MainScreen::~MainScreen() {
    if (backgroundL1.id) UnloadTexture(backgroundL1);
    if (backgroundL2.id) UnloadTexture(backgroundL2);
    if (backgroundL3.id) UnloadTexture(backgroundL3);
}

void MainScreen::load() {
    backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");
}

void MainScreen::update() {
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

    // Draw Texts
    DrawText("MEOWFICANT!", 150, 75, 150, DARKPURPLE);
    DrawText("Press enter to play!", 400, 400, 50, DARKPURPLE);
}