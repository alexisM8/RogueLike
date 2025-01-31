# Roguelike Game

A simple 2D roguelike game built using [Raylib](https://www.raylib.com/).

## Description

This is a roguelike game where you can move a character around a grid using the arrow keys. The game is built with Raylib and features multiple levels, platforms, and enemies.

## Features

- **Basic character movement** with arrow keys.
- **Jumping mechanics** with gravity and platform detection.
- **Multiple levels** with transitions between scenes.
- **Platforms** to jump on and navigate through.
- **Seeking enemies** that chase the player.
- **Collision detection** for platforms, doors, and enemies.
- **Fade transitions** between levels.
- **Boundaries** to prevent the character from going off-screen.
- **Simple 2D graphical representation** of the character, platforms, and enemies.

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