#include "../include/WalkingEnemy.hpp"

WalkingEnemy::WalkingEnemy() 
    : position({1300, 650, 50, 50}), walkingenemySpeed(3.0f), 
      jumpingenemyHeight(2.5f), maxheightReached(false), maxHeight(65.0f) {}

WalkingEnemy::~WalkingEnemy() {
    
}   

void WalkingEnemy::move() {
    // Move the enemy
    if (position.x <= 0) {
        position.x = 1300;
    }
    else {
        position.x -= walkingenemySpeed;
    }

    // Jump
    if (!maxheightReached) {
        position.y -= jumpingenemyHeight;
        if (position.y <= (650 - maxHeight)) {
            maxheightReached = true;
        }
    }
    // Fall back down
    else {
        position.y += jumpingenemyHeight;
        if (position.y >= (700 - 50)) {
            maxheightReached = false;
        }
    }
}

Rectangle WalkingEnemy::getPosition() const {
    return position;
}
