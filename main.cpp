#include "raylib.h"
#include <iostream>

#define SPRITE_COLUMNS 7
#define SPRITE_SCALE 2.0f


bool AtOject(Rectangle rect1, Rectangle rect2) {
        return (rect1.x < rect2.x + rect2.width &&
                rect1.x + rect1.width > rect2.x &&
                rect1.y < rect2.y + rect2.height &&
                rect1.y + rect1.height > rect2.y);
}

int main() {
    // Initialize window
    const int screenWidth = 1400;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Meowficant!!");

    // Set FPS
    SetTargetFPS(60);

    // Load backgrounds
    Texture2D backgroundL1 = LoadTexture("../assets/Backgrounds/background_0.png");
    Texture2D backgroundL2 = LoadTexture("../assets/Backgrounds/background_1.png");
    Texture2D backgroundL3 = LoadTexture("../assets/Backgrounds/background_2.png");

    // Load sprite sheet
    Texture2D spriteSheet = LoadTexture("../assets/Cat/IdleCatb.png");
    Texture2D jumpSprite = LoadTexture("../assets/Cat/JumpCabt.png"); 
    // Define sprite frame size
    float frameWidth = spriteSheet.width / SPRITE_COLUMNS;
    float frameHeight = spriteSheet.height;
    // Animation variables
    float currentFrame = 0.0f;
    float frameTime = 0.05f;  // Time per frame
    float timer = 0.0f;
    // Character position
    Vector2 position = { (screenWidth / 2.0f), (screenHeight / 2.0f) };

    // Rectangle attributes
    // float characterX = screenWidth / 2.0f;  // Start in the center
    // float characterY = screenHeight / 2.0f;
    float movmentSpeed = 10.0f;  // Speed of movement
    float characterWidth =  20.0f + (spriteSheet.width / SPRITE_COLUMNS);
    float characterHeight = ((spriteSheet.height) * 2) - 5.0f;


    // Variables
    float jumpSpeed = -12.5f;  // Negative value for jumping up
    float gravity = 0.5f;      // Gravity pulling down
    float verticalVelocity = 0.0f;  // Velocity in the vertical direction
    float fallSpeed = 0.0f; // Speed of falling
    bool isJumping = false;   // Flag to check if character is in the air
    float groundLevel = screenHeight - characterHeight;  // Ground level
    bool onPlatform = false; // Is character on platform
    float alpha = 0.0f;       // Transparency value for fade effect
    float alpha2 = 0.0f; // Fade effect for death
    bool transitioning = false;  // Flag for the transition
    bool dead = false; // Flag for if character dies
    bool maxheightReached = false; // jumper reaches max height
    float maxHeight = 65.0f;

    // Create scenes
    enum GameScene {
        SCENE_ONE, // First scene 
        SCENE_TWO,  // Second scene
        SCENE_THREE // Third scene
    };
    GameScene currentScene = SCENE_ONE;

    // Define platforms
    Rectangle platforms1[] = {
        { 50, 600, 150, 20 },
        { 400, 500, 125, 20 },
        { 750, 375, 100, 20 },
        { 1050, 250, 100, 20 },
        { 1300, 150, 100, 20 }
    };

    int platformCount1 = sizeof(platforms1) / sizeof(platforms1[0]);
    Rectangle platforms2[] = {
        { 1100, 500, 200, 20 },
        { 900, 300, 50, 20},
        { 700, 300, 25, 20},
        { 500, 200, 25, 20},
        { 300, 500, 100, 20},
        { 100, 150, 50, 20 },
    };
    int platformCount2 = sizeof(platforms2) / sizeof(platforms2[0]);
    Rectangle platforms3[] = {
        { 400, 500, 500, 20 },
    };
    int platformCount3 = sizeof(platforms3) / sizeof(platforms3[0]);

    // Define door
    Rectangle door = { 1325, 75, 50, 75 };
    Rectangle door2 = { 130, 500, 50, 75 };

    // Enemies
    // seekingEnemy starts at x=50, y=100 with width/height 75
    // Speed of movement toward the player
    Rectangle seekingEnemy = { 50, 100, 75, 75 };
    float seekingenemySpeed = 3.0f;  // Speed of movement toward the player
    Rectangle seekingEnemy2 = { 1350, 100, 75, 75 };

    Rectangle walkingEnemy = {1300, 650, 50, 50};
    float walkingenemySpeed = 2.0f;
    float jumpingenemyHeight = 1.5f;

    Rectangle shooters[] = {
        {1350, 325, 20, 20},
        {1350, 475, 20, 20},
        {1350, 175, 20, 20},
    };
    int shootercount = sizeof(shooters) / sizeof(shooters[0]);
    float shooterSpeed = 5.0f;
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Update animation
        timer += GetFrameTime();
        if (timer >= frameTime) {
            timer = 0.0f;
            currentFrame = (int(currentFrame) + 1) % SPRITE_COLUMNS;
        }

        // Boundaries check
        if (position.x < 0) position.x = 0;  // Prevent moving off the left side
        if (position.x + characterWidth > screenWidth) 
            position.x = screenWidth - characterWidth;  // Prevent moving off the right side
        if (position.y < 0) position.y = 0;  // Prevent moving off the top side
        if (position.y + characterHeight > screenHeight) 
            position.y = screenHeight - characterHeight;

        // Create movment
        if (!transitioning && !dead) {
            if (IsKeyDown(KEY_RIGHT)) position.x += movmentSpeed;  // Move right
            if (IsKeyDown(KEY_LEFT)) position.x -= movmentSpeed;   // Move left
            if (IsKeyDown(KEY_DOWN)&& (position.y + characterHeight < screenHeight)) {
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
                // Change the scene
                if (currentScene == SCENE_ONE){
                    currentScene = SCENE_TWO;
                }
                else if (currentScene == SCENE_TWO){
                    currentScene = SCENE_THREE;
                }
                else if (currentScene == SCENE_THREE){
                    seekingEnemy = {50, 100, 75, 75 };
                    seekingEnemy2 = { 1350, 100, 75, 75};
                    currentScene = SCENE_ONE;
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
            
                currentScene = SCENE_ONE;
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
            if (currentScene == SCENE_ONE) {
                for (int i = 0; i < platformCount1; i++) {
                    if (position.x + characterWidth > platforms1[i].x &&
                        position.x < platforms1[i].x + platforms1[i].width &&
                        position.y + characterHeight >= platforms1[i].y &&
                        position.y + characterHeight - verticalVelocity <= platforms1[i].y) {
                        // Landed on the platform
                        position.y = platforms1[i].y - characterHeight;
                        isJumping = false;
                        verticalVelocity = 0.0f;
                        onPlatform = true;
                        break;
                    }
                }
            }
            if (currentScene == SCENE_TWO) {
                for (int i = 0; i < platformCount2; i++) {
                    if (position.x + characterWidth > platforms2[i].x &&
                        position.x < platforms2[i].x + platforms2[i].width &&
                        position.y + characterHeight >= platforms2[i].y &&
                        position.y + characterHeight - verticalVelocity <= platforms2[i].y) {
                        // // Landed on the platform
                        position.y = platforms2[i].y - characterHeight;
                        isJumping = false;
                        verticalVelocity = 0.0f;
                        onPlatform = true;
                        break;
                    }
                }
            }

            if (currentScene == SCENE_THREE) {
                for (int i = 0; i < platformCount3; i++) {
                    if (position.x + characterWidth > platforms3[i].x &&
                        position.x < platforms3[i].x + platforms3[i].width &&
                        position.y + characterHeight >= platforms3[i].y &&
                        position.y + characterHeight - verticalVelocity <= platforms3[i].y){
                        // // Landed on the platform
                        position.y = platforms3[i].y - characterHeight;
                        isJumping = false;
                        verticalVelocity = 0.0f;
                        onPlatform = true;
                        break;
                    }
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

        // Position checks for scene one
        if (currentScene == SCENE_ONE) {
            for (int i = 0; i < platformCount1; i++) {
                if (position.x + characterWidth > platforms1[i].x &&  // Character's right side past platform's left
                    position.x < platforms1[i].x + platforms1[i].width &&  // Character's left side before platform's right
                    position.y + characterHeight >= platforms1[i].y &&  // Character's feet are at or below platform's top
                    position.y + characterHeight <= platforms1[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }
            if (!onPlatform) {
                position.y += 1.0f;
            }
            // Move the enemy
            if (walkingEnemy.x == 0) {
                walkingEnemy.x = 1300;
            }
            else {
                walkingEnemy.x -= walkingenemySpeed;
            }

            // Jump
            if (!maxheightReached) {
                walkingEnemy.y -= jumpingenemyHeight;
                if (walkingEnemy.y <= (groundLevel - maxHeight)) {
                    maxheightReached = true;
                }
            }
            // Fall back down
            else {
                walkingEnemy.y += jumpingenemyHeight;
                if (walkingEnemy.y >= (700 - 50)) {
                    maxheightReached = false;
                }
            }


            // Move shooters
            for (int i = 0; i < shootercount; i++) {
                if (shooters[i].x <= 0) {
                    shooters[i].x = 1300;
                }
                else {
                    shooters[i].x -= shooterSpeed;
                }
            }

            // Check if at door
            if (AtOject({position.x, position.y, characterWidth, characterHeight}, door)) {
                transitioning = true;
            }

            // Check if at walking enemy
            if (AtOject({position.x, position.y, characterWidth, characterHeight}, walkingEnemy)) {
                dead = true;
            }

            // Check if hit shooters
            for (int i = 0; i < shootercount; i++) {
                if (AtOject({position.x, position.y, characterWidth, characterHeight}, shooters[i])) {
                    dead = true;
                }
                
            }
        }
        
        // Position checks for scene two
        if (currentScene == SCENE_TWO) {
            for (int i = 0; i < platformCount2; i++) {
                if (position.x + characterWidth > platforms2[i].x &&  // Character's right side past platform's left
                    position.x < platforms2[i].x + platforms2[i].width &&  // Character's left side before platform's right
                    position.y + characterHeight >= platforms2[i].y &&  // Character's feet are at or below platform's top
                    position.y + characterHeight <= platforms2[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }
            if (!onPlatform) {
                position.y += 1.0f;
            }
            // Check if at door
            if (AtOject({position.x, position.y, characterWidth, characterHeight}, door2)) {
                transitioning = true;
            }
        
        }
        // Position checks for scene three
        if (currentScene == SCENE_THREE) {
            for (int i = 0; i < platformCount3; i++) {
                if (position.x + characterWidth > platforms3[i].x &&  // Character's right side past platform's left
                    position.x < platforms3[i].x + platforms3[i].width &&  // Character's left side before platform's right
                    position.y + characterHeight >= platforms3[i].y &&  // Character's feet are at or below platform's top
                    position.y + characterHeight <= platforms3[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }

            if (!onPlatform) {
                position.y += 1.0f;
            }
            
            // Move the seekingEnemy
            if (seekingEnemy.x < position.x) {
                seekingEnemy.x += seekingenemySpeed;  // Move right
            } else if (seekingEnemy.x > position.x) {
                seekingEnemy.x -= seekingenemySpeed;  // Move left
            }

            if (seekingEnemy.y < position.y) {
                seekingEnemy.y += seekingenemySpeed;  // Move down
            } else if (seekingEnemy.y > position.y) {
                seekingEnemy.y -= seekingenemySpeed;  // Move up
            }

            // Enemy2
            if (seekingEnemy2.x < position.x) {
                seekingEnemy2.x += seekingenemySpeed;  // Move right
            } else if (seekingEnemy2.x > position.x) {
                seekingEnemy2.x -= seekingenemySpeed;  // Move left
            }

            if (seekingEnemy2.y < position.y) {
                seekingEnemy2.y += seekingenemySpeed;  // Move down
            } else if (seekingEnemy2.y > position.y) {
                seekingEnemy2.y -= seekingenemySpeed;  // Move up
            }

            if(AtOject({position.x, position.y, characterWidth, characterHeight}, seekingEnemy) || 
            AtOject({position.x, position.y, characterWidth, characterHeight}, seekingEnemy2)) {
                dead = true;
            }

        }


        // Begin draw
        BeginDrawing();

        // Scene one
        if (currentScene == SCENE_ONE){
            // Make Background
            ClearBackground(RAYWHITE);
            // Draw background images
            float scale = 3.89;
            Rectangle source2 = {0, 0, 288, 180};
            Rectangle dest2 = {0, 0, 1400, 700};
            DrawTexturePro(backgroundL1, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL2, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL3, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);

            // Draw platforms1
            for (int i = 0; i < platformCount1; i++) {
                DrawRectangleRec(platforms1[i], DARKGRAY);
            }

            // Draw current sprite frame
            Rectangle source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
            Rectangle dest = { position.x, position.y, frameWidth * SPRITE_SCALE, frameHeight * SPRITE_SCALE };
            DrawTexturePro(spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);
            DrawRectangleLines(position.x, position.y,characterWidth, characterHeight, RED );

            // Create rectangles
            DrawRectangleRec(door, RED);
            DrawRectangleRec(walkingEnemy, MAROON);
            
            // Shooters
            for (int i = 0; i < shootercount; i++) {
                DrawRectangleRec(shooters[i], GREEN);
            }

            // Draw Texts
            DrawText("Use arrow keys to move!", 10, 10, 20, DARKGRAY);
            DrawText("Press SPACE to Jump!", 10, 30, 20, DARKGRAY);
        }
        else if(currentScene == SCENE_TWO) {
            // Make Background
            ClearBackground(RAYWHITE);

            float scale = 3.89;
            Rectangle source2 = {0, 0, 288, 180};
            Rectangle dest2 = {0, 0, 1400, 700};
            DrawTexturePro(backgroundL1, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL2, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL3, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);

            // Draw platforms2
            for (int i = 0; i < platformCount2; i++) {
                DrawRectangleRec(platforms2[i], RED);
            }

            // Draw current sprite frame
            Rectangle source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
            Rectangle dest = { position.x, position.y, frameWidth * SPRITE_SCALE, frameHeight * SPRITE_SCALE };
            DrawTexturePro(spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);

            // Draw second door
            DrawRectangleRec(door2, BLACK);

            // Draw Texts
            DrawText("Welcome to Scene 2!", 10, 10, 20, RED);
        }
        else if (currentScene == SCENE_THREE){
            // Make Background
            ClearBackground(RAYWHITE);

            // Draw platforms3
            for (int i = 0; i < platformCount3; i++) {
                DrawRectangleRec(platforms3[i], PURPLE);
            }

            float scale = 3.89;
            Rectangle source2 = {0, 0, 288, 180};
            Rectangle dest2 = {0, 0, 1400, 700};
            DrawTexturePro(backgroundL1, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL2, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(backgroundL3, source2, dest2, (Vector2){0,0}, 0.0f, WHITE);

            // Draw current sprite frame
            Rectangle source = { frameWidth * currentFrame, 0, frameWidth, frameHeight };
            Rectangle dest = { position.x, position.y, frameWidth * SPRITE_SCALE, frameHeight * SPRITE_SCALE };
            DrawTexturePro(spriteSheet, source, dest, (Vector2){0, 0}, 0, WHITE);

            // Draw seekingEnemy
            DrawRectangleRec(seekingEnemy, MAROON);
            DrawRectangleRec(seekingEnemy2, MAROON);

            // Draw Texts
            DrawText("Good luck!", 10, 10, 20, PURPLE);
        }

        // Draw fade effect
        if (alpha > 0.0f || alpha2 > 0.0f) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, alpha));
        }
        if (alpha2 > 0.0f) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, alpha2));
        }

        // End drawing
        EndDrawing();
        
    }

    // De-Initialization
    UnloadTexture(spriteSheet);
    UnloadTexture(backgroundL1);
    UnloadTexture(backgroundL2);
    UnloadTexture(backgroundL3);
    CloseWindow();

    return 0;
}