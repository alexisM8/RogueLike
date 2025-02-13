#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "raylib.h"

// Forward declration
class Game;

class MainScreen {
public:
    Texture2D backgroundL1;
    Texture2D backgroundL2;
    Texture2D backgroundL3;

    Game* game;

    MainScreen(Game* game);
    ~MainScreen();
    void render();
    void update();
    void load();
};

#endif