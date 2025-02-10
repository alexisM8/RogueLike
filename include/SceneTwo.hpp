#ifndef SCENE_TWO_HPP
#define SCENE_TWO_HPP

#include "Scene.hpp"
#include "Game.hpp"
#include "Character.hpp"

class SceneTwo : public Scene {
private:
    static const int platformCount = 6;
    Rectangle platforms[platformCount];
    Character character;
    Rectangle door;
    Texture2D backgroundL1;
    Texture2D backgroundL2;
    Texture2D backgroundL3;
    Game* game;
public:
    SceneTwo(Game* game);
    ~SceneTwo();
    void update() override;
    void render() override;
};

#endif
