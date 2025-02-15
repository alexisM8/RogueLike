#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../include/Game.hpp"
#include "raylib.h"

class Character {
protected:
    Game* game;

public:
    Character(Game* game);
    ~Character();
    Vector2 getPosition() const;
    void move(Rectangle platforms[], int platformCount);
    void load();

    // Loaded sprite variables
    Texture2D spriteSheet;
    int spriteColumns;
    float spriteScale;
    float frameWidth;
    float frameHeight;
    float currentFrame;
    float frameTime;
    float timer;

    // Character movement variables
    Vector2 position; // Character position
    float movementSpeed; // Movement speed of character
    float characterWidth; // Width of character
    float characterHeight; // Height of character
    float jumpSpeed;  // Negative value for jumping up
    float gravity; // Gravity pulling down
    float verticalVelocity; // Velocity in the vertical direction
    float fallSpeed; // Speed of falling
    bool isJumping; // Flag to check if character is in the air
    float groundLevel; // Ground level
    bool onPlatform; // Is character on platform
    float alpha; // Transparency value for fade effect
    float alpha2; // Fade effect for death
    bool transitioning;  // Flag for the transition
    bool dead; // Flag for hit by enemy
    
};

#endif