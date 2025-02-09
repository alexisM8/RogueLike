#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Scene.hpp"

class Game {
public:
    Game();       // Constructor
    ~Game();      // Destructor
    void run(); // Game loop
    void setScene(Scene* newScene); // Set Scene
    bool AtOject(Rectangle rect1, Rectangle rect2); // Collision check

    // Screen variables
    int screenWidth = 1400;
    int screenHeight = 700;
    
private:
    void init();  // Initialization
    void update(); // Update logic
    void draw();  // Render frame

    bool running;
    
    // Textures
    Texture2D spriteSheet;
    Texture2D backgroundL1, backgroundL2, backgroundL3;
    
    // Player variables
    Vector2 position;
    int currentFrame;
    
    // Game state
    Scene* currentScene;
};

#endif
