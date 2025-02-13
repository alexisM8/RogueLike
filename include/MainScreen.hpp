#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "raylib.h"

// Forward declration
class Game;

class MainScreen {
public:
    // Background
    Texture2D backgroundL1;
    Texture2D backgroundL2;
    Texture2D backgroundL3;

    // Cats
    Texture2D cat1;
    Texture2D cat2;
    Texture2D cat3;
    Texture2D cat4;
    int spriteColumns;
    float spriteScale;
    float frameWidth;
    float frameHeight;
    float currentFrame;
    float frameTime;
    float timer;
    Vector2 position;

    Game* game;

    MainScreen(Game* game);
    ~MainScreen();
    void render();
    void update();
    void load();
};

#endif