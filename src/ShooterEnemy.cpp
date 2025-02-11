#include "../include/ShooterEnemy.hpp"

ShooterEnemy::ShooterEnemy(Vector2 startPos) {
    shooterenemySpeed = 5.0f;
    position = {startPos.x, startPos.y, 20, 20};
}

ShooterEnemy::~ShooterEnemy() {

}

void ShooterEnemy::move() {
    // Move shooters
    if (position.x <= 0) {
        position.x = 1300;
    }
    else {
        position.x -= shooterenemySpeed;
    }
}

Rectangle ShooterEnemy::getPosition() const {
    return position;
}