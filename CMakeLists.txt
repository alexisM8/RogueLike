cmake_minimum_required(VERSION 3.10)
project(Roguelike)

# Set the path to the Raylib folder
set(RAYLIB_PATH ${CMAKE_SOURCE_DIR}/raylib)

# Include the Raylib headers
include_directories(${RAYLIB_PATH}/src)

# Link to the Raylib static library
link_directories(${RAYLIB_PATH}/build)

# Source code
add_executable(roguelike main.cpp)

# Link Raylib static library
target_link_libraries(roguelike raylib)
