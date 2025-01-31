#include "raylib.h"
#include <iostream>


bool AtDoor(Rectangle rect1, Rectangle rect2) {
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

    // Rectangle attributes
    float characterX = screenWidth / 2.0f;  // Start in the center
    float characterY = screenHeight / 2.0f;
    float movmentSpeed = 10.0f;  // Speed of movement
    float characterWidth = 40.0f;
    float characterHeight = 40.0f;

    // Variables
    float jumpSpeed = -15.0f;  // Negative value for jumping up
    float gravity = 0.5f;      // Gravity pulling down
    float verticalVelocity = 0.0f;  // Velocity in the vertical direction
    float fallSpeed = 0.0f; // Speed of falling
    bool isJumping = false;   // Flag to check if character is in the air
    float groundLevel = screenHeight - characterHeight;  // Ground level
    bool onPlatform = false; // Is character on platform
    float alpha = 0.0f;       // Transparency value for fade effect
    bool transitioning = false;  // Flag for the transition

    // Create scenes
    enum GameScene {
        SCENE_ONE, // First scene 
        SCENE_TWO,  // Second scene
        SCENE_THREE // Third scene
    };
    GameScene currentScene = SCENE_ONE;

    // Define platforms
    Rectangle platforms1[] = {
        { 300, 500, 200, 20 },
        { 700, 400, 200, 20 },
        { 1100, 300, 200, 20 },
        { 500, 200, 200, 20 }
    };
    int platformCount1 = sizeof(platforms1) / sizeof(platforms1[0]);
    Rectangle platforms2[] = {
        { 1100, 500, 200, 20 },
        { 700, 200, 200, 20 },
    };
    int platformCount2 = sizeof(platforms2) / sizeof(platforms2[0]);
    Rectangle platforms3[] = {
        { 400, 500, 500, 20 },
    };
    int platformCount3 = sizeof(platforms3) / sizeof(platforms3[0]);

    // Define door
    Rectangle door = { 1200, groundLevel - 50, 50, 100 };
    Rectangle door2 = { 1200, 480 - 50, 50, 100 };

    // Enemies
    Rectangle seekingEnemy = { 50, 100, 75, 75 }; // seekingEnemy starts at x=50, y=500 with width/height 50
    float seekingenemySpeed = 3.0f;  // Speed of movement toward the player

    
    // Main game loop
    while (!WindowShouldClose()) {
        // Boundaries check
        if (characterX < 0) characterX = 0;  // Prevent moving off the left side
        if (characterX + characterWidth > screenWidth) 
            characterX = screenWidth - characterWidth;  // Prevent moving off the right side
        if (characterY < 0) characterY = 0;  // Prevent moving off the top side
        if (characterY + characterHeight > screenHeight) 
            characterY = screenHeight - characterHeight;

        // Create movment
        if (!transitioning) {
            if (IsKeyDown(KEY_RIGHT)) characterX += movmentSpeed;  // Move right
            if (IsKeyDown(KEY_LEFT)) characterX -= movmentSpeed;   // Move left
            if (IsKeyDown(KEY_DOWN)&& (characterY + characterHeight < screenHeight)) {
                characterY += movmentSpeed; // Move up
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
                    seekingEnemy = {50, 100, 50, 50};
                    currentScene = SCENE_ONE;
                }
                characterX = 100.0f;  // Move character to the next level's starting position
                characterY = groundLevel;
                alpha = 1.0f;  // Cap alpha to fully opaque
                transitioning = false;
            }
        } else if (alpha > 0.0f) {
            alpha -= 0.02f;  // Decrease alpha for fade-in
        }


        onPlatform = false;
        // Apply gravity
        if (isJumping) {
            characterY += verticalVelocity;
            verticalVelocity += gravity;  // Accelerate falling due to gravity
            
            onPlatform = false;

            // Check if character lands on a platform
            if (currentScene == SCENE_ONE) {
                for (int i = 0; i < platformCount1; i++) {
                    if (characterX + characterWidth > platforms1[i].x &&
                        characterX < platforms1[i].x + platforms1[i].width &&
                        characterY + characterHeight >= platforms1[i].y &&
                        characterY + characterHeight - verticalVelocity <= platforms1[i].y) {
                        // Landed on the platform
                        characterY = platforms1[i].y - characterHeight;
                        isJumping = false;
                        verticalVelocity = 0.0f;
                        onPlatform = true;
                        break;
                    }
                }
            }
            if (currentScene == SCENE_TWO) {
                for (int i = 0; i < platformCount2; i++) {
                    if (characterX + characterWidth > platforms2[i].x &&
                        characterX < platforms2[i].x + platforms2[i].width &&
                        characterY + characterHeight >= platforms2[i].y &&
                        characterY + characterHeight - verticalVelocity <= platforms2[i].y) {
                        // // Landed on the platform
                        characterY = platforms2[i].y - characterHeight;
                        isJumping = false;
                        verticalVelocity = 0.0f;
                        onPlatform = true;
                        break;
                    }
                }
            }

            if (currentScene == SCENE_THREE) {
                for (int i = 0; i < platformCount3; i++) {
                    if (characterX + characterWidth > platforms3[i].x &&
                        characterX < platforms3[i].x + platforms3[i].width &&
                        characterY + characterHeight >= platforms3[i].y &&
                        characterY + characterHeight - verticalVelocity <= platforms3[i].y){
                        // // Landed on the platform
                        characterY = platforms3[i].y - characterHeight;
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
            if (characterY >= groundLevel) {
                characterY = groundLevel;  // Ensure character stays on the ground
                isJumping = false;         // Stop jumping
                verticalVelocity = 0.0f;   // Reset vertical velocity
            }

        }

        // Position checks for scene one
        if (currentScene == SCENE_ONE) {
            for (int i = 0; i < platformCount1; i++) {
                if (characterX + characterWidth > platforms1[i].x &&  // Character's right side past platform's left
                    characterX < platforms1[i].x + platforms1[i].width &&  // Character's left side before platform's right
                    characterY + characterHeight >= platforms1[i].y &&  // Character's feet are at or below platform's top
                    characterY + characterHeight <= platforms1[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }
            if (!onPlatform) {
                characterY += 0.5f;
            }
            // Check if at door
            if (AtDoor({characterX, characterY, characterWidth, characterHeight}, door)) {
                transitioning = true;
            }
        }
        
        // Position checks for scene two
        if (currentScene == SCENE_TWO) {
            for (int i = 0; i < platformCount2; i++) {
                if (characterX + characterWidth > platforms2[i].x &&  // Character's right side past platform's left
                    characterX < platforms2[i].x + platforms2[i].width &&  // Character's left side before platform's right
                    characterY + characterHeight >= platforms2[i].y &&  // Character's feet are at or below platform's top
                    characterY + characterHeight <= platforms2[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }
            if (!onPlatform) {
                characterY += 0.5f;
            }
            // Check if at door
            if (AtDoor({characterX, characterY, characterWidth, characterHeight}, door2)) {
                transitioning = true;
            }
        
        }
        // Position checks for scene three
        if (currentScene == SCENE_THREE) {
            for (int i = 0; i < platformCount3; i++) {
                if (characterX + characterWidth > platforms3[i].x &&  // Character's right side past platform's left
                    characterX < platforms3[i].x + platforms3[i].width &&  // Character's left side before platform's right
                    characterY + characterHeight >= platforms3[i].y &&  // Character's feet are at or below platform's top
                    characterY + characterHeight <= platforms3[i].y + 5) {
                    // // Landed on the platform
                    onPlatform = true;
                }
            }

            if (!onPlatform) {
                characterY += 0.5f;
            }
            
            // Move the seekingEnemy
            if (seekingEnemy.x < characterX) {
                seekingEnemy.x += seekingenemySpeed;  // Move right
            } else if (seekingEnemy.x > characterX) {
                seekingEnemy.x -= seekingenemySpeed;  // Move left
            }

            if (seekingEnemy.y < characterY) {
                seekingEnemy.y += seekingenemySpeed;  // Move down
            } else if (seekingEnemy.y > characterY) {
                seekingEnemy.y -= seekingenemySpeed;  // Move up
            }

            if(AtDoor({characterX, characterY, characterWidth, characterHeight}, seekingEnemy)) {
                transitioning = true;
            }

        }


        // Begin draw
        BeginDrawing();

        // Scene one
        if (currentScene == SCENE_ONE){
            // Make Background
            ClearBackground(RAYWHITE);

            // Draw platforms1
            for (int i = 0; i < platformCount1; i++) {
                DrawRectangleRec(platforms1[i], DARKGRAY);
            }

            // Create rectangles
            DrawRectangle(characterX, characterY, characterWidth, characterHeight, BLACK);
            DrawRectangleRec(door, RED);

            // Draw Texts
            DrawText("Use arrow keys to move!", 10, 10, 20, DARKGRAY);
            DrawText("Press SPACE to Jump!", 10, 30, 20, DARKGRAY);
        }
        else if(currentScene == SCENE_TWO) {
            // Make Background
            ClearBackground(GRAY);

            // Draw platforms2
            for (int i = 0; i < platformCount2; i++) {
                DrawRectangleRec(platforms2[i], RED);
            }

            // Create rectangles
            DrawRectangle(characterX, characterY, characterWidth, characterHeight, BLACK);
            DrawRectangleRec(door2, BLACK);

            // Draw Texts
            DrawText("Welcome to Scene 2!", 10, 10, 20, RED);
        }
        else if (currentScene == SCENE_THREE){
            // Make Background
            ClearBackground(DARKGRAY);

            // Draw platforms3
            for (int i = 0; i < platformCount3; i++) {
                DrawRectangleRec(platforms3[i], PURPLE);
            }

            // Create rectangles
            DrawRectangle(characterX, characterY, characterWidth, characterHeight, BLACK);

            // Draw seekingEnemy
            DrawRectangleRec(seekingEnemy, MAROON);

            // Draw Texts
            DrawText("Good luck!", 10, 10, 20, PURPLE);
        }

        // Draw fade effect
        if (alpha > 0.0f) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, alpha));
        }

        // End drawing
        EndDrawing();
        
    }

    // De-Initialization
    CloseWindow();

    return 0;
}