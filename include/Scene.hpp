#ifndef SCENE_HPP
#define SCENE_HPP

class Game; // Forward declaration, to avoid circular import

class Scene {
protected:
    Game* game; // Reference to the game instance

public:
    Scene(Game* game) : game(game) {}
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~Scene() = default;
};

#endif
