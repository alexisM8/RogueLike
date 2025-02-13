cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

# Set the path to the Raylib folder
set(RAYLIB_PATH ${CMAKE_SOURCE_DIR}/raylib)

# Add Raylib with correct flags
add_subdirectory(${RAYLIB_PATH})

# Include the Raylib headers
include_directories(${RAYLIB_PATH}/src)

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
)

# Create the executable
add_executable(roguelike ${SOURCES})

# Link Raylib static library
target_link_libraries(roguelike raylib)



