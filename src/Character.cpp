#include "../include/Character.hpp"
#include "../include/SceneOne.hpp"
#include "../include/SceneTwo.hpp"
#include "../include/SceneThree.hpp"
#include <random>

// Constants
constexpr float CHARACTER_SCALE = 2.0f;
constexpr float MOVEMENT_SPEED = 12.5f;
constexpr float JUMP_SPEED = -12.5f;
constexpr float GRAVITY = 0.5f;
constexpr float FALL_SPEED = 0.0f;
constexpr float GROUND_OFFSET = 5.0f; // Offset adjustment for ground-level calculation
constexpr float ALPHA_INCREMENT = 0.02f;

Character::Character(Game* game) : game(game) {
    this->load();
    movementSpeed = MOVEMENT_SPEED;
    characterWidth =  20.0f + (spriteSheet.width / spriteColumns);
    characterHeight = (spriteSheet.height * CHARACTER_SCALE) - GROUND_OFFSET;
    jumpSpeed = JUMP_SPEED;
    gravity = GRAVITY;
    verticalVelocity = 0.0f;
    fallSpeed = FALL_SPEED;
    isJumping = false;
    groundLevel = game->screenHeight - characterHeight;
    onPlatform = false;
    alpha = 0.0f;
    alpha2 = 0.0f;
    transitioning = false;
    dead = false;
}

Character::~Character() {
    UnloadTexture(spriteSheet);
}

void Character::load() {
    // Initialize random engine with a random seed
    std::random_device rd;  
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(1, 4);

    // Generate the random number
    int randomNumber = dist(gen);
    // Cat picker
    switch (randomNumber) {
        case 1:
            spriteSheet = LoadTexture("../assets/Cat/IdleCatb.png");
            break;
        case 2:
            spriteSheet = LoadTexture("../assets/Cat/IdleCatt.png");
            break;
        case 3:
            spriteSheet = LoadTexture("../assets/Cat/IdleCatd.png");
            break;
        case 4:
            spriteSheet = LoadTexture("../assets/Cat/IdleCattt.png");
            break;
        default:
            spriteSheet = LoadTexture("../assets/Cat/IdleCatb.png");
    }
    spriteColumns = 7;
    spriteScale = CHARACTER_SCALE;
    frameWidth = spriteSheet.width / spriteColumns;
    frameHeight = spriteSheet.height;
    currentFrame = 0.0f;
    frameTime = 0.05f;
    timer = 0.0f;
    position = { game->screenWidth / 2.0f, game->screenHeight / 2.0f };
}

void Character::move(Rectangle platforms[], int platformCount) {
    timer += GetFrameTime();
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame = (int(currentFrame) + 1) % spriteColumns;
    }

    // Boundaries check
    if (position.x < 0) position.x = 0;
    if (position.x + characterWidth > game->screenWidth) 
        position.x = game->screenWidth - characterWidth;
    if (position.y < 0) position.y = 0;
    if (position.y + characterHeight > game->screenHeight) 
        position.y = game->screenHeight - characterHeight;

    // Movement Input
    if (!transitioning && !dead) {
        if (IsKeyDown(KEY_RIGHT)) position.x += movementSpeed;
        if (IsKeyDown(KEY_LEFT)) position.x -= movementSpeed;
        if (IsKeyDown(KEY_DOWN) && position.y + characterHeight < game->screenHeight) {
            position.y += movementSpeed;
        }

        // Jumping input
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            verticalVelocity = jumpSpeed; // Apply jump velocity
            isJumping = true;
        }
    }

    // Handle transitions
    if (transitioning) {
        alpha += ALPHA_INCREMENT;
        if (alpha >= 1.0f) {
            if (dynamic_cast<SceneOne*>(game->getCurrentScene())){
                game->setScene(new SceneTwo(game));
            } else if (dynamic_cast<SceneTwo*>(game->getCurrentScene())) {
                game->setScene(new SceneThree(game));
            }
            position.x = 100.0f;
            position.y = groundLevel;
            alpha = 1.0f;
            transitioning = false;
        }
    } else if (alpha > 0.0f) {
        alpha -= ALPHA_INCREMENT;
    }

    if (dead) {
        alpha2 += ALPHA_INCREMENT;
        if (alpha2 >= 1.0f) {
            position.x = 100.0f;
            position.y = groundLevel;
            game->setScene(new SceneOne(game));
            alpha2 = 1.0f;
            dead = false;
        }
    } else if (alpha2 > 0.0f) {
        alpha2 -= ALPHA_INCREMENT;
    }

    // Gravity and Platform Collision
    bool wasOnPlatform = onPlatform;
    onPlatform = false;

    // Apply gravity if not on a platform
    if (isJumping) {
        position.y += verticalVelocity;
        verticalVelocity += gravity; // Gravity applies jumping and falling
    }

    // Check platform collisions
    for (int i = 0; i < platformCount; i++) {
        if (position.x + characterWidth > platforms[i].x &&
            position.x < platforms[i].x + platforms[i].width &&
            position.y + characterHeight >= platforms[i].y &&
            position.y + characterHeight - verticalVelocity <= platforms[i].y) {
            // Landed on a platform
            position.y = platforms[i].y - characterHeight;
            isJumping = false;
            verticalVelocity = 0.0f;
            onPlatform = true;
            break;
        }
    }

    // Start falling naturally
    if (!onPlatform && wasOnPlatform) {
        isJumping = true; 
    }

    // Ground collision
    if (position.y >= groundLevel) {
        position.y = groundLevel;
        isJumping = false;
        verticalVelocity = 0.0f;
        onPlatform = true;
    }
}


Vector2 Character::getPosition() const {
    return position;
}