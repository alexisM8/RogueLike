#include "../include/SeekingEnemy.hpp"
#include "../include/Character.hpp"

SeekingEnemy::SeekingEnemy(Vector2 startPos) {
    seekingenemySpeed = 3.5f;
    position = {startPos.x, startPos.y, 50, 50 };
}

SeekingEnemy::~SeekingEnemy() {

}

void SeekingEnemy::move(Vector2 charPosition) {
    // Move the seekingEnemy
    if (position.x < charPosition.x) {
        position.x += seekingenemySpeed;  // Move right
    } else if (position.x > charPosition.x) {
        position.x -= seekingenemySpeed;  // Move left
    }

    if (position.y < charPosition.y) {
        position.y += seekingenemySpeed;  // Move down
    } else if (position.y > charPosition.y) {
        position.y -= seekingenemySpeed;  // Move up
    }
}

Rectangle SeekingEnemy::getPosition() const {
    return position;
}