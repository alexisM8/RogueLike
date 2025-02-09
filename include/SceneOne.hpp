#ifndef SCENE_ONE_HPP
#define SCENE_ONE_HPP

#include "Scene.hpp"
#include "Game.hpp"
#include "WalkingEnemy.hpp"
#include "Character.hpp"
#include "raylib.h"

class SceneOne : public Scene {
private:
    static const int platformCount = 5;
    Rectangle platforms[platformCount];
    WalkingEnemy walkingEnemy;
    Character character;
    Rectangle door;
    Texture2D backgroundL1;
    Texture2D backgroundL2;
    Texture2D backgroundL3;
public:
    SceneOne(Game* game);
    ~SceneOne();
    void update() override;
    void render() override;
};

#endif
