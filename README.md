# Roguelike Game

A simple 2D roguelike game built using [Raylib](https://www.raylib.com/).

## Description

This is a 2D action-adventure game built with Raylib, where you control a character that navigates through platforms, jumps, and avoids enemies. The game features smooth character movement, gravity, and platform detection, with multiple levels and scene transitions. You will face different types of enemies while navigating challenging environments, with fade effects and boundaries to keep you within the playable area.

## Project Features

### Character Movement & Physics
- Smooth movement using arrow keys.
- Jumping mechanics with gravity and platform collision detection.

### Level & Scene Management
- Multiple scenes with transitions between levels.
- Fade effects for seamless level changes.
- Boundaries to keep the character within the playable area.

### Environment & Interaction
- Platforms for navigation and strategic movement.
- Doors for transitioning between scenes.
- Collision detection for platforms, enemies, and interactive objects.

### Enemies & Challenges
- Walking and shooting enemies with different movement behaviors.
- Enemy collision detection that affects the player's status (e.g., death or respawn).

### Graphics & Visuals
- Simple 2D sprite-based representation of the character, enemies, and environment.
- Background layers for added depth.
- Scaled textures and animations for a polished visual experience.

## Requirements

- A C++ compiler (such as `g++` or `clang++`).
- CMake for building the project.

## Installation

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/roguelike.git
    cd roguelike
    ```

2. Build the project:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

This will automatically use the included Raylib in the repository to build the game.

## How to Run the Game

Once the project is built, you can run the game by navigating to the `build` directory and executing the generated binary:

```bash
./roguelike