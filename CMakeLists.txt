cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

# Find Raylib installed on the system
find_package(raylib REQUIRED)

# Gather all source files
set(SOURCES 
    main.cpp
    src/Game.cpp
    src/SceneOne.cpp
    src/SceneTwo.cpp
    src/SceneThree.cpp
    src/WalkingEnemy.cpp
    src/SeekingEnemy.cpp
    src/ShooterEnemy.cpp
    src/Character.cpp
    src/MainScreen.cpp
)

# Create the executable
add_executable(roguelike ${SOURCES})

# Link with Raylib
target_link_libraries(roguelike raylib)
