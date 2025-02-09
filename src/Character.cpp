#include "../include/Character.hpp"

Character::Character() {
    spriteSheet = LoadTexture("../assets/Cat/IdleCatb.png");
    sprite_cloumns = 7;
    sprite_Scale = 2.0f;
    frameWidth = spriteSheet.width / sprite_cloumns;
    frameHeight = spriteSheet.height;
    currentFrame = 0.0f;
    frameTime = 0.05f;
    timer = 0.0f;
    position = { (1400 / 2.0f), (700 / 2.0f) };
    movmentSpeed = 12.5f;
    characterWidth =  20.0f + (spriteSheet.width / sprite_cloumns);
    characterHeight = ((spriteSheet.height) * 2) - 5.0f;
    jumpSpeed = -12.5f;
    gravity = 0.5f;      // Gravity pulling down
    verticalVelocity = 0.0f;
    fallSpeed = 0.0f; // Speed of falling
    isJumping = false;   // Flag to check if character is in the air
    groundLevel = 700 - characterHeight;  // Ground level
    onPlatform = false; // Is character on platform
    alpha = 0.0f;       // Transparency value for fade effect
    alpha2 = 0.0f; // Fade effect for death
    transitioning = false;  // Flag for the transition
    dead = false;
}
Character::~Character() {
    UnloadTexture(spriteSheet);
}


void Character::move(Rectangle platforms[], int platformCount) {
    timer += GetFrameTime();
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame = (int(currentFrame) + 1) % sprite_cloumns;
    }
    // Boundaries check
    if (position.x < 0) position.x = 0;  // Prevent moving off the left side
    if (position.x + characterWidth > 1400) 
        position.x = 1400 - characterWidth;  // Prevent moving off the right side
    if (position.y < 0) position.y = 0;  // Prevent moving off the top side
    if (position.y + characterHeight > 700) 
        position.y = 700 - characterHeight;

    // Create movment
    if (!transitioning && !dead) {
        if (IsKeyDown(KEY_RIGHT)) position.x += movmentSpeed;  // Move right
        if (IsKeyDown(KEY_LEFT)) position.x -= movmentSpeed;   // Move left
        if (IsKeyDown(KEY_DOWN)&& (position.y + characterHeight < 700)) {
            position.y += movmentSpeed; // Move up
        }

        // Jumping input
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            // Start jump if not already jumping
            verticalVelocity = jumpSpeed;
            isJumping = true;
        }
    }
    if (transitioning) {
        alpha += 0.02f;  // Increase alpha for fade-out
        if (alpha >= 1.0f) {
            position.x = 100.0f;  // Move character to the next level's starting position
            position.y = groundLevel;
            alpha = 1.0f;  // Cap alpha to fully opaque
            transitioning = false;
        }
    } else if (alpha > 0.0f) {
        alpha -= 0.02f;  // Decrease alpha for fade-in
    }
    if (dead) {
        alpha2 += 0.02f;
        if (alpha2 >= 1.0f) {
            position.x = 100.0f;  // Move character to the next level's starting position
            position.y = groundLevel;
            alpha2 = 1.0f;  // Cap alpha to fully opaque
            dead = false;
        }
    }
    else if (alpha2 > 0.0f) {
        alpha2 -= 0.02f;  // Decrease alpha for fade-in
    }
    onPlatform = false;
    // Apply gravity
    if (isJumping) {
        position.y += verticalVelocity;
        verticalVelocity += gravity;  // Accelerate falling due to gravity
        
        onPlatform = false;

        // Check if character lands on a platform
        for (int i = 0; i < platformCount; i++) {
            if (position.x + characterWidth > platforms[i].x &&
                position.x < platforms[i].x + platforms[i].width &&
                position.y + characterHeight >= platforms[i].y &&
                position.y + characterHeight - verticalVelocity <= platforms[i].y) {
                // Landed on the platform
                position.y = platforms[i].y - characterHeight;
                isJumping = false;
                verticalVelocity = 0.0f;
                onPlatform = true;
                break;
            }
        }

        // If not on any platform, apply gravity
        if (!onPlatform) {
            isJumping = true;
        }

        // Check if the character has landed on the ground
        if (position.y >= groundLevel) {
            position.y = groundLevel;  // Ensure character stays on the ground
            isJumping = false;         // Stop jumping
            verticalVelocity = 0.0f;   // Reset vertical velocity
        }

    }
    for (int i = 0; i < platformCount; i++) {
        if (position.x + characterWidth > platforms[i].x &&  // Character's right side past platform's left
            position.x < platforms[i].x + platforms[i].width &&  // Character's left side before platform's right
            position.y + characterHeight >= platforms[i].y &&  // Character's feet are at or below platform's top
            position.y + characterHeight <= platforms[i].y + 5) {
            // // Landed on the platform
            onPlatform = true;
        }
    }
    if (!onPlatform) {
        position.y += 1.0f;
    }

}

Vector2 Character::getPosition() const {
    return position;
}