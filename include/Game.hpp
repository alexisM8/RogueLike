#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Scene.hpp"
#include "Character.hpp"
#include "../include/MainScreen.hpp"
#include "../include/WinScreen.hpp"

class Character;

class Game {
public:
    Game(); 
    ~Game(); 
    void run(); // Game loop
    void setScene(Scene* newScene); // Set Scene
    bool AtOject(Rectangle rect1, Rectangle rect2); // Collision check
    void cleanup();
    Scene* getCurrentScene() const;

    // Screen variables
    int screenWidth = 1400;
    int screenHeight = 700;

    bool running;
    bool firstRun;
    bool wonGame;

    Character* character;  
    
private:
    void init(); 
    void update(); 

    
    // Textures
    Texture2D spriteSheet;
    Texture2D backgroundL1, backgroundL2, backgroundL3;
    
    // Player variables
    Vector2 position;
    int currentFrame;
    
    // Game state
    Scene* currentScene;
    MainScreen* mainSceen;
    WinScreen* winScreen;
};

#endif
