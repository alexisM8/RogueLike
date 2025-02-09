#ifndef WALKING_ENEMY_HPP
#define WALKING_ENEMY_HPP

#include "raylib.h"

class WalkingEnemy {
private:
    
public:
    WalkingEnemy();
    ~WalkingEnemy();
    Rectangle getPosition() const;
    void move();
    Rectangle position;
    float walkingenemySpeed;
    float jumpingenemyHeight;
    bool maxheightReached;
    float maxHeight;
    
};


#endif