#ifndef SHOOTER_ENEMY_HPP
#define SHOOTER_ENEMY_HPP

#include "raylib.h"

class ShooterEnemy {
private:
    Rectangle position;
    float shooterenemySpeed;

public:
    ShooterEnemy(Vector2 startPos);
    ~ShooterEnemy();
    Rectangle getPosition() const;
    void move();
};

#endif