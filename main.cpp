#include "raylib.h"

const int tileSize = 50;  // Size of each tile
const int mapWidth = 15;   // Number of tiles horizontally
const int mapHeight = 12;   // Number of tiles vertically

// Tile types 
enum TileType { EMPTY, WALL };

// A simple map with walls and empty spaces
TileType map[mapHeight][mapWidth] = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
};

void DrawMap() {
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            Color tileColor = (map[x][y] == WALL) ? DARKGRAY : LIGHTGRAY;
            DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, tileColor);
        }
    }
}

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rogue LIKE!!");

    // Set FPS
    SetTargetFPS(60);

    // Character properties
    // Texture2D characterImage = LoadTexture("character.png"); // Reserved for image
    // DrawTexture(characterTexture, characterX, characterY, WHITE); // use this too 

    float characterX = screenWidth / 2.0f;  // Start in the center
    float characterY = screenHeight / 2.0f;
    float movmentSpeed = 5.0f;  // Speed of movement
    float characterWidth = 50.0f;
    float characterHeight = 50.0f;

    // Main game loop
    while (!WindowShouldClose()) {

        // Create movment
        if (IsKeyDown(KEY_RIGHT)) characterX += movmentSpeed;  // Move right
        if (IsKeyDown(KEY_LEFT)) characterX -= movmentSpeed;   // Move left
        if (IsKeyDown(KEY_UP)) characterY -= movmentSpeed;     // Move up
        if (IsKeyDown(KEY_DOWN)) characterY += movmentSpeed;   // Move down
        
        // Boundaries check
        if (characterX < 0) characterX = 0;  // Prevent moving off the left side
        // Prevent Moving off rightside
        if (characterX + characterWidth > screenWidth) characterX = screenWidth - characterWidth;
        if (characterY < 0) characterY = 0;  // Prevent moving off the top side
        // Prevent moving off bottom side, this will probably change.
        if (characterY + characterHeight > screenHeight) characterY = screenHeight - characterHeight;
        
        // Begin draw
        BeginDrawing();

        // Make Background
        ClearBackground(RAYWHITE);

        DrawMap();

        // Create Character
        DrawRectangle(characterX, characterY, characterWidth, characterHeight, BLACK);



        DrawText("Goodluck!", 50, 50, 20, DARKGRAY);
        DrawText("Wzzzzzz", 10, 10, 20, YELLOW); 
        DrawText(" DarkBlue ", 10, 40, 20,DARKBLUE);

        // End drawing
        EndDrawing();
        
    }

    // De-Initialization
    CloseWindow();

    return 0;
}