#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "raylib.h"

class Character {
private:

public:
    Character();
    ~Character();
    Vector2 getPosition() const;
    void move(Rectangle platforms[], int platformCount);
    Texture2D spriteSheet;
    int sprite_cloumns;
    float sprite_Scale;
    float frameWidth;
    float frameHeight;
    float currentFrame;
    float frameTime;
    float timer;
    Vector2 position;
    float movmentSpeed;
    float characterWidth;
    float characterHeight;
    float jumpSpeed;  // Negative value for jumping up
    float gravity;      // Gravity pulling down
    float verticalVelocity;  // Velocity in the vertical direction
    float fallSpeed; // Speed of falling
    bool isJumping;   // Flag to check if character is in the air
    float groundLevel;  // Ground level
    bool onPlatform; // Is character on platform
    float alpha;       // Transparency value for fade effect
    float alpha2; // Fade effect for death
    bool transitioning;  // Flag for the transition
    bool dead; // Flag for hit by enemy
    
};

#endif