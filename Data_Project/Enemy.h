#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    int x, y;
    int dx, dy;
public:
    Enemy();

    int getX() const;
    int getY() const;

    void move(const int grid[][40], int ts);
    void reverseDirection();
    void setPosition(int a, int b);
    void increaseSpeed(float speedMultiplier);

};

#endif // ENEMY_H
