#include "../include/Game.hpp"
#include "raylib.h"
#include "../include/SceneOne.hpp"
#include <iostream>

Game::Game() {
    // Initialize window
    const int screenWidth = 1400;
    const int screenHeight = 700;

    // Current Scene
    currentScene = nullptr;
}
Game::~Game() {
    if (currentScene) delete currentScene;
}

void Game::setScene(Scene* newScene) {
    if (currentScene) delete currentScene;  // Clean up old scene
    currentScene = newScene;
}

Scene* Game::getCurrentScene() const {
    return currentScene;
}

bool Game::AtOject(Rectangle rect1, Rectangle rect2) {
    return (rect1.x < rect2.x + rect2.width &&
            rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height &&
            rect1.y + rect1.height > rect2.y);
}

void Game::run() {
    InitWindow(screenWidth, screenHeight, "Meowficant!!");
    // Set first scene
    setScene(new SceneOne(this));
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (currentScene) {
            currentScene->update();
            currentScene->render();
        }

        EndDrawing();
    }

    CloseWindow();
}
