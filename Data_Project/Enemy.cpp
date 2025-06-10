#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy() {
    x = y = 300;
    dx = 4 - rand() % 8;
    dy = 4 - rand() % 8;
}

void Enemy::setPosition(int a, int b)
{
    this->x = a;
    this->y = b;
}

void Enemy::move(const int grid[][40], int tileSize) {
    // Store previous position
    float prevX = x;
    float prevY = y;

    // Move the enemy
    x += dx;
    y += dy;

    // Get grid coordinates
    int gridX = x / tileSize;
    int gridY = y / tileSize;

    // Ensure the enemy is within bounds
    if (gridX < 0) gridX = 0;
    if (gridX > 39) gridX = 39;
    if (gridY < 0) gridY = 0;
    if (gridY > 24) gridY = 24;

    // Boundary collision (border tiles)
    if (grid[gridY][gridX] == 1) {
        // Reflect from borders
        if (x < 0 || x > 40 * tileSize - 1) dx = -dx;
        if (y < 0 || y > 25 * tileSize - 1) dy = -dy;

        // Restore previous position
        x = prevX;
        y = prevY;

        // Modify direction slightly for more natural movement
        dx = -dx;
        dy = -dy;

        // Adjust position to avoid getting stuck
        x += dx * 2;
        y += dy * 2;
    }

    // Collision with player's filled areas
    if (grid[gridY][gridX] == 4 || grid[gridY][gridX] == 5) {
        // Reverse direction on collision with filled areas
        dx = -dx;
        dy = -dy;

        // Restore previous position
        x = prevX;
        y = prevY;

        // Adjust position to avoid getting stuck
        x += dx * 2;
        y += dy * 2;
    }
}

void Enemy::reverseDirection() {
    // Reverse the direction of movement
    dx = -dx;
    dy = -dy;

    // Move the enemy slightly to prevent it from getting stuck
    x += dx * 2;
    y += dy * 2;
}

int Enemy::getX() const { return x; }
int Enemy::getY() const { return y; }

void Enemy::increaseSpeed(float speedMultiplier) {
    // Multiply the current direction by the speed multiplier
    dx *= speedMultiplier;
    dy *= speedMultiplier;
}