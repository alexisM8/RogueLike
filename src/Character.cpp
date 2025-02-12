#include "../include/Character.hpp"
#include "../include/SceneOne.hpp"
#include "../include/SceneTwo.hpp"
#include "../include/SceneThree.hpp"

// Constants
constexpr float SCREEN_WIDTH = 1400.0f;
constexpr float SCREEN_HEIGHT = 700.0f;
constexpr float CHARACTER_SCALE = 2.0f;
constexpr float MOVEMENT_SPEED = 12.5f;
constexpr float JUMP_SPEED = -12.5f;
constexpr float GRAVITY = 0.5f;
constexpr float FALL_SPEED = 0.0f;
constexpr float GROUND_OFFSET = 5.0f; // Offset adjustment for ground-level calculation
constexpr float ALPHA_INCREMENT = 0.02f;

Character::Character(Game* game) : game(game) {
    spriteSheet = LoadTexture("../assets/Cat/IdleCatb.png");
    spriteColumns = 7;
    spriteScale = CHARACTER_SCALE;
    frameWidth = spriteSheet.width / spriteColumns;
    frameHeight = spriteSheet.height;
    currentFrame = 0.0f;
    frameTime = 0.05f;
    timer = 0.0f;
    position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    movementSpeed = MOVEMENT_SPEED;
    characterWidth =  20.0f + (spriteSheet.width / spriteColumns);
    characterHeight = (spriteSheet.height * CHARACTER_SCALE) - GROUND_OFFSET;
    jumpSpeed = JUMP_SPEED;
    gravity = GRAVITY;
    verticalVelocity = 0.0f;
    fallSpeed = FALL_SPEED;
    isJumping = false;
    groundLevel = SCREEN_HEIGHT - characterHeight;
    onPlatform = false;
    alpha = 0.0f;
    alpha2 = 0.0f;
    transitioning = false;
    dead = false;
}


Character::~Character() {
    UnloadTexture(spriteSheet);
}


void Character::move(Rectangle platforms[], int platformCount) {
    timer += GetFrameTime();
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame = (int(currentFrame) + 1) % spriteColumns;
    }
    // Boundaries check
    if (position.x < 0) position.x = 0;  // Prevent moving off the left side
    if (position.x + characterWidth > 1400) 
        position.x = 1400 - characterWidth;  // Prevent moving off the right side
    if (position.y < 0) position.y = 0;  // Prevent moving off the top side
    if (position.y + characterHeight > 700) 
        position.y = 700 - characterHeight;

    // Create movement
    if (!transitioning && !dead) {
        if (IsKeyDown(KEY_RIGHT)) position.x += movementSpeed;  // Move right
        if (IsKeyDown(KEY_LEFT)) position.x -= movementSpeed;   // Move left
        if (IsKeyDown(KEY_DOWN)&& (position.y + characterHeight < 700)) {
            position.y += movementSpeed; // Move up
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
            // Check which scene is next
            if (dynamic_cast<SceneOne*>(game->getCurrentScene())){
                game->setScene(new SceneTwo(game));
            }
            else if (dynamic_cast<SceneTwo*>(game->getCurrentScene())) {
                game->setScene(new SceneThree(game));
            }
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
            game->setScene(new SceneOne(game));
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