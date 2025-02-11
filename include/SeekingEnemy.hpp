#ifndef SEEKING_ENEMY_HPP
#define SEEKING_ENEMY_HPP

#include "raylib.h"
#include "../include/Character.hpp"

class SeekingEnemy {
private:
    Rectangle position;
    float seekingenemySpeed;
    
public:
    SeekingEnemy(Vector2 startpos);
    ~SeekingEnemy();
    Rectangle getPosition() const;
    void move(Vector2 charPosition);
    
};


#endif